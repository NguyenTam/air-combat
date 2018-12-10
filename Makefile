MAIN_DIR = src
TEST_DIR = test

.PHONY: main test

all: main test

main:
	$(MAKE) -C $(MAIN_DIR)

test:
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) -C $(MAIN_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean

run-game:
	$(MAKE) -C $(MAIN_DIR) run
