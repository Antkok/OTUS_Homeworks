THIS_DIR=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))

COMPONENT_NAME=$(shell basename $(THIS_DIR))

PREFIX_DIR=$(THIS_DIR)/../../_result
BUILD_DIR=$(THIS_DIR)/../../_build/$(COMPONENT_NAME)

COMPONENT_DIR=googletest-release-1.8.1
COMPONENT_AR=$(COMPONENT_DIR).tar.gz

CMAKE_ARGS := \
 -DCMAKE_INSTALL_PREFIX=$(PREFIX_DIR) \
 -DCMAKE_BUILD_TYPE=Release

all: $(COMPONENT_AR) build

$(COMPONENT_AR):
	wget https://github.com/google/googletest/archive/release-1.8.1.tar.gz -O $@
	tar -xf $@ -C $(THIS_DIR)

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
	cmake $(CMAKE_ARGS) $(THIS_DIR)/$(COMPONENT_DIR) && \
	cmake --build $(BUILD_DIR) -- -j$(shell nproc) && \
	$(MAKE) install

clean:
	rm -rf $(BUILD_DIR)

remove:
	rm -rf $(COMPONENT_DIR) $(COMPONENT_AR)

