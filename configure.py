#!/usr/bin/env python
# -*- encoding: utf-8 -*-

from os import system

def readIntInRange( low, high ):
    while True:
        try:
            n = int( raw_input('Your choice: ') )
            if n >= low and n <= high:
                return n
        except Exception:
            pass

PATTERN = """#!/usr/bin/env sh
mkdir -p %(MODE)s
cd %(MODE)s
cmake %(OPTIONS)s ..
make
cd ..
"""

options=[
    ("Choose your compilation mode :",
        ["release", "debug"],
        ["MODE", "BUILD_FLAGS"],
        [
            ["release", "debug"],
            ["", "-DCMAKE_BUILD_TYPE=Debug"]
        ]
    ),
    ("Do you want to use OpenMP with CPT ?",
        ["yes", "no"],
        ["CPT_OMP"],
        [
            ["-DCPT_WITH_OMP=1", ""]
        ]
    ),
    ("Do you want to use OpenMP with DAE ?",
        ["yes", "no"],
        ["DAE_OMP"],
        [
            ["-DDAE_WITH_OMP=1", ""]
        ]
    )
]

OPTIONS = "%(CPT_OMP)s %(DAE_OMP)s %(BUILD_FLAGS)s"

responses = {}

for question in options:
    print question[0]
    i = 1
    for answer in question[1]:
        print i, ")", answer
        i += 1
    choice = readIntInRange( 1, i-1 ) - 1
    for i in range(len(question[2])):
        responses[ question[2][i] ] = question[3][i][choice]


responses[ "OPTIONS" ] = OPTIONS % responses
del responses['CPT_OMP']
del responses['DAE_OMP']
del responses['BUILD_FLAGS']

print "\n\nCorresponding bash script : "
print PATTERN % responses

print "\nDo you want to save the script to a file or execute it directly ?"
print "1) Record"
print "2) Execute"
print "3) Do nothing and quit"
choice = readIntInRange( 1, 3 )

if choice == 1:
    filename = raw_input("Choose a file name: (build.sh by default)")
    if filename == "":
        filename = "build.sh"
    script = file( filename, 'w' )
    script.write( PATTERN % responses )
    script.close()
    print "Do not forget to do a chmod + x to start the script."
elif choice == 2:
    system( PATTERN % responses )
