DEBUG_FALG = -O3 -DNDEBUG # -g
CXXFLAGS += -Wall -Wextra $(DEBUG_FALG) -std=c++11
CFLAGS += -Wall -Wextra $(DEBUG_FALG)
LDFLAGS += $(DEBUG_FALG)
CU_CFLAGS = -Wall -fwrapv -march=native

.PHONY: all
all: build

SUB_TARGET = random main generator wrap progress config
OBJS = $(addprefix bin/,$(addsuffix .o,$(SUB_TARGET)))
THIRD_PARTY = bin/cubiomes.a
CUBIOMES_NAME = finders generator layers
CUBIOMES_OBJ = $(addprefix bin/cu_,$(addsuffix .o,$(CUBIOMES_NAME)))

include $(addprefix bin/,$(addsuffix .d,$(SUB_TARGET)))

reverse_seed: $(OBJS) $(THIRD_PARTY)
	$(CXX) -o $@ $^ $(LDFLAGS)

bin/%.d: src/%.c bin
	$(CC) -MM -MP $< $(CXXFLAGS) | sed 's,\($*\)\.o[ :]*,bin/\1.o $@ : ,g' > $@

bin/%.d: src/%.cpp bin
	$(CXX) -MM -MP $< $(CXXFLAGS) | sed 's,\($*\)\.o[ :]*,bin/\1.o $@ : ,g' > $@

bin/%.o: src/%.c bin
	$(CC) -c -o $@ $< $(CFLAGS)

bin/%.o: src/%.cpp bin
	$(CXX) -c -o $@ $< $(CXXFLAGS)


$(CUBIOMES_OBJ): bin/cu_%.o: cubiomes/%.c
	$(CC) -c -o $@ $^ $(CU_CFLAGS)

bin/cubiomes.a: $(CUBIOMES_OBJ)
	$(AR) rs $@ $^

bin:
	mkdir bin

.PHONY: build
build: reverse_seed

.PHONY: test
test: reverse_seed
	./test.py

.PHONY: clean
clean:
	-rm -f $(OBJS) $(THIRD_PARTY) $(CUBIOMES_OBJ)
	-rm -f $(OBJS:.o=.d) $(CUBIOMES_OBJ:.o=.d)
