THIS_DIR=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))
MAKEFILE_CONF := $(THIS_DIR)/Makefile.conf
include $(MAKEFILE_CONF)

COMPONENT_NAME=$(shell basename $(THIS_DIR))

PREFIX_DIR=$(THIS_DIR)/../_result
CONTRIB_DIR=$(THIS_DIR)/../contrib
BUILD_DIR=$(THIS_DIR)/../_build/$(COMPONENT_NAME)

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && \
	cmake -DCMAKE_PREFIX_PATH=$(PREFIX_DIR) \
	      -DCMAKE_ENABLE_DEBUG=$(CONFIG_ENABLE_DEBUG) \
	      -DCMAKE_ENABLE_TEST=$(CONFIG_ENABLE_TEST) \
	      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	      $(THIS_DIR)
	cmake --build $(BUILD_DIR) -- -j$(shell nproc)
	mv $(BUILD_DIR)/compile_commands.json $(THIS_DIR)

contrib:
	$(MAKE) -C $(CONTRIB_DIR)

test doc package: $(BUILD_DIR)
	$(MAKE) $(MAKECMDGOALS) -C $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
