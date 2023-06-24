TARGET   = ./a.out

SRCDIR   = src
OUTDIR   = out

BINDIR   = $(OUTDIR)/bin
OBJDIR   = $(OUTDIR)/obj
DEPDIR   = $(OUTDIR)/dep

CFLAGS   = -Wall -O2
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

SRCS     = $(wildcard $(SRCDIR)/*.c)
OBJS     = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS     = $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.d)))

$(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@ $<

# The empty rule is required to handle the case where the dependency file is deleted.
$(DEPS):

include $(wildcard $(DEPS))

$(BINDIR):
	@mkdir -p $@
$(OBJDIR):
	@mkdir -p $@
$(DEPDIR):
	@mkdir -p $@

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET) data.md $(OUTDIR)
	@echo clean completed.

.PHONY: out
out:
	$(BINDIR)/$(TARGET)
