#!/bin/bash

PROJECT=$1
BINTRAY_API_KEY=$2

DEB_PATH=$(ls ../_result/dist/*.deb)
DEB_NAME=$(basename $DEB_PATH)
VERSION=$(echo $DEB_NAME | egrep -o '[0-9.]{3,}')
curl -T $DEB_PATH -ua-zvg:$BINTRAY_API_KEY "https://api.bintray.com/content/a-zvg/otus-cpp/$PROJECT/$VERSION/$DEB_NAME;deb_distribution=bionic;deb_component=main;deb_architecture=amd64;publish=1"

# Подготовка структуры файлов документации для деплоя на gh-pages
git clone https://github.com/a-zvg/otus-cpp.git -b gh-pages ../_result/doc/gh-pages # документация предыдущих проектов
mv ../_result/doc/gh-pages/* ../_result/doc/
rm -rf ../_result/doc/gh-pages ../_result/doc/$PROJECT # удаление загруженной доки по текущему проекту
mv ../_result/doc/html ../_result/doc/$PROJECT
cat << EOF > ../_result/doc/index.html
<!DOCTYPE html>
<html>
<body>
<h2>Документация</h2>
EOF
for d in `ls -1 ../_result/doc/ | grep ^[0-9]`; do
    echo "<a href="$d/index.html">$d</a><br/>" >> ../_result/doc/index.html
done
cat << EOF >> ../_result/doc/index.html
</body>
</html>
EOF
