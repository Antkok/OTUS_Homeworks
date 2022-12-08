THIS_DIR=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))

CONTRIB_LIST=$(shell ls -d $(THIS_DIR)/*/)

all clean remove:
	for m in $(CONTRIB_LIST); do \
	$(MAKE) -C $$m $(MAKECMDGOALS) || \
	exit 1; \
	done
