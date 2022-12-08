THIS_DIR=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))

COMPONENT_NAME=$(shell basename $(THIS_DIR))

PREFIX_DIR=$(THIS_DIR)/../../_result
BUILD_DIR=$(THIS_DIR)/../../_build/$(COMPONENT_NAME)

COMPONENT_DIR=boost_asio_1_73_0
COMPONENT_AR=$(COMPONENT_DIR).tar.gz

all: $(COMPONENT_DIR) build

$(COMPONENT_DIR):
	tar -xf $(COMPONENT_AR) -C $(THIS_DIR)

build:
	mkdir -p $(PREFIX_DIR)/include
	cp -r $(COMPONENT_DIR)/boost $(PREFIX_DIR)/include/

clean:
	rm -rf $(BUILD_DIR)

remove:
	rm -rf $(COMPONENT_DIR)

