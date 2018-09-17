###########################################################################
#                                                                         #
#                        Makefile NPOT-B                                  #
#                                                                         #
###########################################################################
ifndef ROOT
include ../../common/root/root.mak
endif

all : sip megaco
.NOTPARALLEL: sip megaco

sip :
	$(MAKE) -f Makefile_sip
megaco :
	$(MAKE) -f Makefile_megaco

purify purestrip purify_force purestrip_force:
	$(MAKE) -f Makefile_sip $@
	$(MAKE) -f Makefile_megaco $@
