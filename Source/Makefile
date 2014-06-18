ifeq ($(strip $(SATURNSDK)),)
$(error "Please set the environment variable SATURNSDK to point to the root directory of the SEGA Saturn SDK")
endif

ifndef TOPDIR
export TOPDIR		:= $(shell cd ../ && pwd)
export TOPSRC		= $(TOPDIR)/Source
export TARGETDIR	= $(TOPDIR)/Bin
export OBJSDIR		= $(TOPDIR)/Obj
endif

SOURCEDIR = Source

PROJECT	:= MLD52
TARGET	:= $(PROJECT)
COFFTARGET := $(TARGETDIR)/$(TARGET).elf
OUTFILE	= $(TARGETDIR)/$(TARGET).bin

CROSS_COMPILER = $(SATURNSDK)/toolchain/bin/saturn-sh2-

CC = $(CROSS_COMPILER)gcc
LD = $(CROSS_COMPILER)ld
OBJCOPY = $(CROSS_COMPILER)objcopy

SGLINC=$(SATURNSDK)/include/sgl
SGLLIB=$(SATURNSDK)/lib/sgl

CFLAGS = -c -m2 -I$(SGLINC) -I$(TOPSRC)/Headers
LDFLAGS = -m2 -L$(SGLLIB) -Xlinker --format=elf32-sh -Xlinker -T$(LDFILE) -Xlinker -Map -Xlinker $(MAPFILE) -Xlinker -e -Xlinker ___Start -nostartfiles

SYSOBJS = $(SGLLIB)/sglarea.o
LDFILE = $(TOPSRC)/MLD52.lnk
MAPFILE = $(TARGET:.elf=.map)

debug: BUILD	= Debug
debug: BUILD_TYPE = debug
debug: BUILD_DEF = DEBUG
debug: TARGET := $(TARGET)D
debug: CFLAGS += -g
debug: LIBS = -lsgl
debug: $(TARGET)


ifneq ($(OBJSDIR), $(CURDIR))
TARGETDIR:
	@mkdir -p $(TARGETDIR)

OBJSDIR:
	@mkdir -p $(OBJSDIR)

CFILES			:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.c)))
export VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))
export OBJS		:= $(CFILES:.c=.o)

$(TARGET): OBJSDIR TARGETDIR
	$(MAKE) -C $(OBJSDIR) -f $(TOPSRC)/Makefile $(BUILD_TYPE)

else

$(COFFTARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(SYSOBJS) $(OBJS) $(LIBS) -o $@

$(TARGET): $(COFFTARGET)
	$(OBJCOPY) -O binary $(COFFTARGET) $(OUTFILE)
#	$(CC) -o $(OUTFILE) $(OBJS) $(LIBS)

%.o: %.c
	printf "Compiling...\n"
	$(CC) -MMD -MP -MF $*.d $(CFLAGS) -I$(SGLINC) $< -o $@
#2> $*.cmsgs

-include $(OBJSDIR)/*.d

endif

.SUFFIXES: .asm

