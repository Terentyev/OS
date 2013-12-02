Prepare
=======

Needed packages for test:
    * app-cdr/cdrtools (>=3.00)
    * sys-boot/grub (>=0.97-r10)
    * app-emulation/virtualbox (>=4.0.12)

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

    VBoxManage createvm --name vmOS
    VBoxManage registervm ~/.VirtualBox/Machines/vmOS/vmOS.vbox
    VBoxManage modifyvm vmOS --memory 32 --boot1 dvd
    VBoxManage storagectl vmOS --name bootcd --add sata --bootable on

Or you can run:

    make create_vm

Create bootloading ISO-image and kernel
=======================================

Build OS kernel:

    make

See also
========

For more information about GRUB see [grub_doc]


[grub_doc]: http://orgs.man.ac.uk/documentation/grub/grub_3.html#SEC11 "GRUB documentation"
