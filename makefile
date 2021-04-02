CC = g++
CPPFLAGS = -Wall -g -pthread
BUILD = build/app

# set up more directory variables as needed
SRC_FOLDERS = actors game graphics gui items monsters story 
USER_INCLUDES = $(addprefix src/, $(SRC_FOLDERS))
INC = $(USER_INCLUDES)		# list all directories you want to have included in CPATH on the same line here
INC_PARAMS = $(foreach d, $(INC), -I$d)

# search for header files
HEADERS :=\
	$(wildcard src/*/*.hpp)

# search for source code files
SOURCE_CODE=\
	$(wildcard src/*/*.cpp)

# set the location in folder hierarchy where to store object binaries
OBJECTS=\
	$(SOURCE_CODE:src/%.cpp=obj/%.o)

# dependency files
DEP = $(OBJECTS:obj/%.o=dep/%.d)

# sort removes duplicates---we do not want to compile an object twice
OBJ_SUBDIR=\
	$(sort $(foreach sc, $(OBJECTS), $(dir $(sc))))

all: $(OBJ_SUBDIR) $(OBJ_SUBDIR:obj/%=dep/%) $(BUILD) 

# create targets for making object subdirectories if needed
define MKDIR_OBJ_FOLDER =
$(1):
	$$(info *** creating $(1) directory ***)
	mkdir -p $(1)
endef
$(foreach objdir,\
	$(OBJ_SUBDIR),\
	$(eval \
		$(call MKDIR_OBJ_FOLDER, $(objdir))\
	)\
)

# create targets for making dependency subdirectories if needed
define MKDIR_DEP_FOLDER =
$(1:obj/%=dep/%):
	$$(info *** creating $(1) directory ***)
	mkdir -p $(1:obj/%=dep/%)
endef
$(foreach objdir,\
	$(OBJ_SUBDIR),\
	$(eval \
		$(call MKDIR_DEP_FOLDER, $(objdir))\
	)\
)

# order-only prerequisites |
# Targets listed after the Sheffer stroke (such as a directory) may change timestamp,
# but this will not trigger execution of the defining target.
# Create targets for compiling source code, and note the object files are the target names
define COMPILE_SOURCE_CODE =
$(1:src/%.cpp=obj/%.o) : $(1) | $(dir $(1:src/%=obj/%))
	$(CC) \
	$(INC_PARAMS) \
	-MMD -MF $(1:src/%.cpp=dep/%.d) \
	-c $(CPPFLAGS) $(1) -o \
	$(dir $(1:src/%=obj/%))$(notdir $(1:%.cpp=%.o))
endef
$(foreach sc,\
	$(SOURCE_CODE),\
	$(eval \
		$(call COMPILE_SOURCE_CODE, $(sc))\
	)\
)

# double check when running make to see what files we have
compile_info:
	$(info )
	$(info *** Project Header Files ***)
	$(foreach header, $(HEADERS), $(info $(header)))
	$(info )
	$(info *** Project Source Code Files ***)
	$(foreach sc, $(SOURCE_CODE), $(info $(sc)))
	$(info )

$(BUILD): compile_info $(HEADERS) $(OBJECTS)
	$(CC) $(CPPFLAGS) $(INC_PARAMS) -o $@ $(OBJECTS)

.PHONY: clean cleandep compile_info

clean:
	rm $(OBJECTS) $(BUILD)

cleandep:
	rm $(DEP)

-include $(DEP)
