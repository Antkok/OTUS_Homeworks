/// @file
/// @brief Файл с реализацией поисковика файлов-дубликатов

#include "bayan_finder.h"
#include <algorithm>
#include <memory>
#include <regex>

std::size_t FileMeta::bulkSize_ = 0;

BayanFinder::BayanFinder(const Options& options)
{
    setOptions(options);
}

void BayanFinder::setOptions(const Options& options)
{
    options_ = options;
    if (options.hash_ == HashType::CRC)
    {
        hash_ = std::make_unique<CrcHash>();
    }
    else
    {
        hash_ = std::make_unique<BoostHash>();
    }
}

std::vector<FileMetas> BayanFinder::findBayans()
{
    if (files_.empty())
    {
        files_ = scanDirs(options_.targets_, options_.excludes_, options_.patterns_, options_.minSize_,  options_.depth_);
    }

    FileMetas duplSizeFiles;
    while (!(duplSizeFiles = getDuplSizeFiles(files_)).empty())
    {
        auto bayans = getDuplFileGroups(duplSizeFiles);
        if (!bayans.empty())
        {
            return bayans;
        }
    }
    return {};
}

FileMetas BayanFinder::scanDirs(const std::vector<std::string>& targets, const std::vector<std::string>& excludes,
        const std::vector<std::string>& patterns, std::size_t minSize, int depth) const
{
    auto files = std::unordered_map<std::string, std::size_t>();
    for (auto& target : targets)
    {
        fs::recursive_directory_iterator it(target), end;
        for (; it != end; ++it)
        {
            if (fs::is_regular_file(it->status()) && !fs::is_symlink(it->symlink_status()))
            {
                if (patterns.empty())
                {
                    addBySize(it->path(), minSize, files);
                }
                for (auto& pattern : patterns)
                {
                    std::regex expr(pattern, std::regex_constants::icase);
                    if (std::regex_match(it->path().filename().native(), expr))
                    {
                        addBySize(it->path(), minSize, files);
                    }
                }
            }
            else if (fs::is_directory(it.status()))
            {
                if (it.depth() >= depth)
                {
                    it.no_push();
                }
                auto absPath = fs::canonical(*it);
                for (auto& exclude : excludes)
                {
                    if (absPath == fs::canonical(exclude))
                    {
                        it.no_push();
                    }
                }
            }
        }
    }
    FileMetas fileMetas;
    fileMetas.reserve(files.size());
    std::transform(files.begin(), files.end(), std::back_inserter(fileMetas),
            [](auto& pair)
            {
                return FileMeta(pair.first, pair.second);
            });
    return fileMetas;
}

void BayanFinder::addBySize(fs::path file, std::size_t minSize, std::unordered_map<std::string, std::size_t>& files) const
{
    auto fileSize = fs::file_size(file);
    if (fileSize >= minSize)
    {
        files.insert(std::make_pair(file.native(), fileSize));
    }
}

FileMetas BayanFinder::getDuplSizeFiles(FileMetas& files) const
{
    FileMetas duplFiles;

    if (!files.empty())
    {
        while (true)
        {
            auto it = std::partition(files.begin(), files.end(),
                    [size = files[0].size_](const auto& f)
                    {
                        return f.size_ != size;
                    });
            duplFiles.insert(duplFiles.end(), std::make_move_iterator(it), std::make_move_iterator(files.end()));

            files.erase(it, files.end());

            if (duplFiles.size() > 1 || duplFiles.empty())
            {
                break;
            }
            else
            {
                duplFiles.clear();
            }
        }
    }
    return duplFiles;
}

std::vector<FileMetas> BayanFinder::getDuplFileGroups(FileMetas& files) const
{
    std::vector<FileMetas> duplFileGroups;
    for (std::size_t i = 0; i < files.size(); ++i)
    {
        auto it = std::partition(++files.begin(), files.end(),
                [this, file = files[0]](auto& f) mutable
                {
                    return !compare(file, f);
                });
        if (std::distance(it, files.end()) > 0)
        {
            FileMetas fs;
            fs.push_back(std::move(files[0]));
            fs.insert(fs.end(), std::make_move_iterator(it), std::make_move_iterator(files.end()));

            duplFileGroups.push_back(std::move(fs));
        }
        files.erase(it, files.end());
        files.erase(files.begin());
    }
    return duplFileGroups;
}

bool BayanFinder::compare(FileMeta& file1, FileMeta& file2) const
{
    std::size_t step = 0;
    while ((step * FileMeta::bulkSize_) < file1.size_)
    {
        auto steps = std::min(file1.bulkHashes_.size(), file2.bulkHashes_.size());
        for (; step < steps; ++step)
        {
            if (file1.bulkHashes_[step] != file2.bulkHashes_[step])
            {
                return false;
            }
        }
        if (file1.bulkHashes_.size() < file2.bulkHashes_.size())
        {
            hash_->hash(file1);
        }
        else
        {
            hash_->hash(file2);
        }
    }
    return true;
}
