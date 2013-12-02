OSNAME=OS
KDIR=./kernel
KBIN=kernel.bin
ISO=iso
ISOBOOT=./$(ISO)/boot
ISONAME=$(OSNAME).$(ISO)
STAGE=boot/grub/stage2_eltorito
MKISO=mkisofs
#MKISO=genisoimage
MKISOFLAGS=-R -b $(STAGE) -no-emul-boot -boot-load-size 4 -boot-info-table
ISOGRUB=$(ISOBOOT)/grub
MENULST=$(ISOGRUB)/menu.lst
STAGE2=$(ISOGRUB)/stage2_eltorito
MAKE=make
VBOXMANAGE=VBoxManage
VMMEMORY=32
VMNAME=vm$(OSNAME)
VMPATH=~/.VirtualBox/Machines/$(VMNAME)
VMRUNNING:=$(shell $(VBOXMANAGE) showvminfo $(VMNAME) | grep -e 'State:[ ]\+running')
VMSTRGNAME=bootcd

all: $(STAGE2) $(MENULST) $(ISONAME)

$(ISONAME): CHECKVM KERNEL
	mkdir -p $(ISOBOOT)
	cp $(KDIR)/$(KBIN) $(ISOBOOT)/
	$(MKISO) $(MKISOFLAGS) -o $@ $(ISO)

$(STAGE2):
	sudo mount /boot
	cp /boot/grub/stage_eltorito $(STAGE2)

$(MENULST):
	mkdir -p $(ISOGRUB)
	echo "# See http://orgs.man.ac.uk/documentation/grub/grub_5.html#SEC25" > $(MENULST)
	echo "default 0"                                                       >> $(MENULST)
	echo "timeout 5"                                                       >> $(MENULST)
	echo ""                                                                >> $(MENULST)
	echo "# My OS"                                                         >> $(MENULST)
	echo "title OS"                                                        >> $(MENULST)
	echo "root  (cd)"                                                      >> $(MENULST)
	echo "kernel /boot/$(KBIN)"                                            >> $(MENULST)

CHECKVM:
ifneq " $(VMRUNNING)" " "
	echo "Stop virtual machine first"
	echo "For example run: make stop_vm"
	exit 1
endif

KERNEL:
	cd $(KDIR); $(MAKE) clean; $(MAKE); cd ..

create_vm:
	$(VBOXMANAGE) createvm --name $(VMNAME)
	$(VBOXMANAGE) registervm $(VMPATH)/$(VMNAME).vbox
	$(VBOXMANAGE) modifyvm $(VMNAME) --memory $(VMMEMORY) --boot1 dvd
	$(VBOXMANAGE) storagectl $(VMNAME) --name $(VMSTRGNAME) --add sata --bootable on

start_vm:
	$(VBOXMANAGE) storageattach $(VMNAME) --storagectl $(VMSTRGNAME) --port 1 --type dvddrive --medium $(ISONAME)
	$(VBOXMANAGE) startvm $(VMNAME) --type headless

stop_vm:
	$(VBOXMANAGE) controlvm $(VMNAME) poweroff

remove_vm:
ifneq " $(VMRUNNING)" " "
	$(MAKE) stop_vm
endif
	$(VBOXMANAGE) storagectl $(VMNAME) --name $(VMSTRGNAME) --remove
	$(VBOXMANAGE) unregistervm $(VMNAME) --delete

clean:
	rm -f os.iso iso/boot/kernel.bin
	cd $(KDIR); $(MAKE) clean; cd ..
