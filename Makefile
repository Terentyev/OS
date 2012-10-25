KDIR=./kernel
KBIN=kernel.bin
ISO=iso
ISOBOOT=./$(ISO)/boot
STAGE=boot/grub/stage2_eltorito
MKISO=mkisofs
#MKISO=genisoimage
MKISOFLAGS=-R -b $(STAGE) -no-emul-boot -boot-load-size 4 -boot-info-table
MAKE=make
VMRUNNING:=$(shell VBoxManage showvminfo OS | grep -e 'State:[ ]\+running')

all: os.iso

os.iso: CHECKVM KERNEL
	cp $(KDIR)/$(KBIN) $(ISOBOOT)/
	$(MKISO) $(MKISOFLAGS) -o $@ $(ISO)

CHECKVM:
ifneq " $(VMRUNNING)" " "
	echo "Stop virtual machine first"
	exit 1
endif

KERNEL:
	cd $(KDIR); $(MAKE) clean; $(MAKE); cd ..

clean:
	rm -f os.iso iso/boot/kernel.bin
	cd $(KDIR); $(MAKE) clean; cd ..
