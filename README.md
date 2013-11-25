check-msvc
==========
install mingw
launch msys
change to source directory
>configure
>make
from a cmd prompt cd to source directory
>pushd src\.libs
>call LIB /DEF:libcheck-0.dll.def /MACHINE:X86 /NAME:libcheck-0 /OUT:libcheck.lib
>popd
et voila.
