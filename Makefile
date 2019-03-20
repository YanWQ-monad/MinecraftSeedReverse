DEBUG_FALG = -O3 -DNDEBUG # -g
CXXFLAGS += -Wall -Wextra $(DEBUG_FALG) -std=c++11
CFLAGS += -Wall -Wextra $(DEBUG_FALG)
LDFLAGS += $(DEBUG_FALG)
CU_CFLAGS = -Wall -fwrapv -march=native

.PHONY: all
all: reverse_seed

SUB_TARGET = random main generator wrap progress config
OBJS = $(addprefix build/,$(addsuffix .o,$(SUB_TARGET)))
THIRD_PARTY = build/cubiomes.a
CUBIOMES_NAME = finders generator layers
CUBIOMES_OBJ = $(addprefix build/cu_,$(addsuffix .o,$(CUBIOMES_NAME)))

include $(addprefix build/,$(addsuffix .d,$(SUB_TARGET)))

reverse_seed: $(OBJS) $(THIRD_PARTY)
	$(CXX) -o $@ $^ $(LDFLAGS)

build/%.d: src/%.c
	$(CC) -MM -MP $< $(CXXFLAGS) | sed 's,\($*\)\.o[ :]*,build/\1.o $@ : ,g' > $@

build/%.d: src/%.cpp
	$(CXX) -MM -MP $< $(CXXFLAGS) | sed 's,\($*\)\.o[ :]*,build/\1.o $@ : ,g' > $@

build/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

build:
	mkdir build

$(CUBIOMES_OBJ): build/cu_%.o: cubiomes/%.c
	$(CC) -c -o $@ $^ $(CU_CFLAGS)

build/cubiomes.a: $(CUBIOMES_OBJ)
	$(AR) rs $@ $^

.PHONY: clean
clean:
	-rm -f $(OBJS) $(THIRD_PARTY) $(CUBIOMES_OBJ)
	-rm -f $(OBJS:.o=.d) $(CUBIOMES_OBJ:.o=.d)
