Prepare
=======

Needed packages for test:
    * app-cdr/cdrtools (3.00)
    * sys-boot/grub (0.97-r10)
    * app-emulation/virtualbox (4.0.12)

If your distributive don't have a cdrtools package, you can use
use genisoimage (1.1.11), but you should fix ./Makefile:

    replace

        MKISO=mkisofs
        #MKISO=genisoimage

    to

        #MKISO=mkisofs
        MKISO=genisoimage

Create virtual machine
======================

Prepare VirtualBox machine:

    VBoxManage createvm --name OS
    VBoxManage registervm ~/.VirtualBox/Machines/OS/OS.vbox
    VBoxManage modifyvm OS --memory 32 --boot1 dvd
    VBoxManage storagectl OS --name bootcd --add sata --bootable on

Create bootloading ISO-image
============================

Need to prepare directory for bootloaded iso:

    mkdir -p iso/boot/grub

Copy GRUB file:

    cp /boot/grub/stage2_eltorito iso/boot/grub/

Edit menu.lst:

    vim iso/boot/grub/menu.lst

Build OS kernel:

    make

Attach bootloading ISO-image
============================

And attach:

    VBoxManage storageattach OS --storagectl bootcd --port 1 --type dvddrive --medium os.iso

See also
========

For more information about GRUB see [grub_doc]


[grub_doc]: http://orgs.man.ac.uk/documentation/grub/grub_3.html#SEC11 "GRUB documentation"
