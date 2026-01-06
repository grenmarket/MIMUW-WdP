all: $(SOURCE_CODE) $(EXE)
	make build
	make test
	make testmem

test: $(SOURCE_CODE) $(EXE)
	echo "Valgrind=false"
	echo ""
	@for dir in $(TESTS); do \
  		echo Paczka $$dir:; \
  		$(TESTER) $$dir false $(TESTS_MAX);  \
  		echo ;\
	done;

testmem: $(SOURCE_CODE) $(EXE)
	echo "Valgrind=true"
	echo ""
	@for dir in $(TESTS); do \
  		echo Paczka $$dir:; \
  		$(TESTER) $$dir true $(TESTS_MAX_VALGRIND);  \
  		echo ;\
	done;

build: $(SOURCE_CODE)
	$(COMPILER) @opcje $(SOURCE_CODE) -o $(EXE)