##########################################################################
# Copyright (c) 2009, ETH Zurich.
# All rights reserved.
#
# This file is distributed under the terms in the attached LICENSE file.
# If you do not find this file, copies can be found by writing to:
# ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
##########################################################################

machines = {
    'nos1'   : {'ncores'      : 8,
                'machine_name' : 'nos1',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 4,
                'perfcount_type': 'intel',
                'tickrate'    : 2660,
                'boot_timeout': 600},
    'nos2'   : {'ncores'      : 8,
                'machine_name' : 'nos2',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 4,
                'perfcount_type': 'intel',
                'tickrate'    : 2660,
                'boot_timeout': 600},
    'nos3'   : {'ncores'      : 8,
                'machine_name' : 'nos3',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 4,
                'perfcount_type': 'intel',
                'tickrate'    : 2660,
                'boot_timeout': 600},

    'nos4'   : {'ncores'      : 4,
                'machine_name' : 'nos4',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 2,
                'perfcount_type': 'amd0f',
                'tickrate'    : 2800},
    'nos5'   : {'ncores'      : 4,
                'machine_name' : 'nos5',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 2,
                'perfcount_type': 'amd0f',
                'tickrate'    : 2800},
    'nos6'   : {'ncores'      : 4,
                'machine_name' : 'nos6',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 2,
                'perfcount_type': 'amd0f',
                'tickrate'    : 2800},

    'sbrinz1': {'ncores'      : 16,
                'machine_name' : 'sbrinz1',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 4,
                'perfcount_type': 'amd10',
                'tickrate'    : 2500},
    'sbrinz2': {'ncores'      : 16,
                'machine_name' : 'sbrinz2',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 4,
                'perfcount_type': 'amd10',
                'tickrate'    : 2500},

    'gruyere': {'ncores'      : 32,
                'machine_name' : 'gruyere',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 4,
                'perfcount_type': 'amd10',
                'tickrate'    : 2000},

    'ziger1':  {'ncores'      : 24,
                'machine_name' : 'ziger1',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 6,
                'perfcount_type': 'amd10',
                'tickrate'    : 2400.367},
    'ziger2':  {'ncores'      : 24,
                'machine_name' : 'ziger2',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 6,
                'perfcount_type': 'amd10',
                'tickrate'    : 2400.367},

    'tomme1':  {'ncores'      : 16,
                'machine_name' : 'tomme1',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 8,
                'perfcount_type': 'intel',
                'tickrate'    : 2270,
                'boot_timeout': 360,
                'kernel_args' : ['serial=0x2f8']},
    'tomme2':  {'ncores'      : 16,
                'machine_name' : 'tomme2',
                'bootarch' : 'x86_64',
                'buildarchs' : ['x86_64', 'x86_32'],
                'cores_per_socket': 8,
                'perfcount_type': 'intel',
                'tickrate'    : 2270,
                'boot_timeout': 360,
                'kernel_args' : ['serial=0x2f8']},

    'appenzeller': {'ncores'      : 48,
                    'machine_name' : 'appenzeller',
                    'bootarch' : 'x86_64',
                    'buildarchs' : ['x86_64', 'x86_32'],
                    'cores_per_socket': 12,
                    'perfcount_type': 'amd10',
                    'tickrate'    : 2200,
                    'boot_timeout': 360},

    'gottardo': {'ncores'      : 32,
                 'machine_name' : 'gottardo',
                 'bootarch' : 'x86_64',
                 'buildarchs' : ['x86_64', 'x86_32'],
                 'cores_per_socket': 16,
                 'perfcount_type': 'intel',
                 'tickrate'    : 1870,
                 'boot_timeout': 360},

    'westmere': {'ncores'      : 40,
                 'machine_name' : 'westmere',
                 'bootarch' : 'x86_64',
                 'buildarchs' : ['x86_64', 'x86_32'],
                 'cores_per_socket': 10,
                 'perfcount_type': 'intel',
                 'tickrate'    : 2394,
                 'boot_timeout': 360},

    'nos1-32'   : {'ncores'      : 8,
                   'machine_name' : 'nos1',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 4,
                   'perfcount_type': 'intel',
                   'tickrate'    : 2660,
                   'boot_timeout': 600},
    'nos2-32'   : {'ncores'      : 8,
                   'machine_name' : 'nos2',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 4,
                   'perfcount_type': 'intel',
                   'tickrate'    : 2660,
                   'boot_timeout': 600},
    'nos3-32'   : {'ncores'      : 8,
                   'machine_name' : 'nos3',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 4,
                   'perfcount_type': 'intel',
                   'tickrate'    : 2660,
                   'boot_timeout': 600},

    'nos4-32'   : {'ncores'      : 4,
                   'machine_name' : 'nos4',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 2,
                   'perfcount_type': 'amd0f',
                   'tickrate'    : 2800},
    'nos5-32'   : {'ncores'      : 4,
                   'machine_name' : 'nos5',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 2,
                   'perfcount_type': 'amd0f',
                   'tickrate'    : 2800},
    'nos6-32'   : {'ncores'      : 4,
                   'machine_name' : 'nos6',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 2,
                   'perfcount_type': 'amd0f',
                   'tickrate'    : 2800},

    'sbrinz1-32': {'ncores'      : 16,
                   'machine_name' : 'sbrinz1',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 4,
                   'perfcount_type': 'amd10',
                   'tickrate'    : 2500},
    'sbrinz2-32': {'ncores'      : 16,
                   'machine_name' : 'sbrinz2',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 4,
                   'perfcount_type': 'amd10',
                   'tickrate'    : 2500},

    'gruyere-32': {'ncores'      : 32,
                   'machine_name' : 'gruyere',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 4,
                   'perfcount_type': 'amd10',
                   'tickrate'    : 2000},

    'ziger1-32':  {'ncores'      : 24,
                   'machine_name' : 'ziger1',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 6,
                   'perfcount_type': 'amd10',
                   'tickrate'    : 2400.367},
    'ziger2-32':  {'ncores'      : 24,
                   'machine_name' : 'ziger2',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 6,
                   'perfcount_type': 'amd10',
                   'tickrate'    : 2400.367},

    'tomme1-32':  {'ncores'      : 16,
                   'machine_name' : 'tomme1',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 8,
                   'perfcount_type': 'intel',
                   'tickrate'    : 2270,
                   'boot_timeout': 360,
                   'kernel_args' : ['serial=0x2f8']},
    'tomme2-32':  {'ncores'      : 16,
                   'machine_name' : 'tomme2',
                   'bootarch' : 'x86_32',
                   'buildarchs' : ['x86_64', 'x86_32'],
                   'cores_per_socket': 8,
                   'perfcount_type': 'intel',
                   'tickrate'    : 2270,
                   'boot_timeout': 360,
                   'kernel_args' : ['serial=0x2f8']},

    'appenzeller-32': {'ncores'      : 48,
                       'machine_name' : 'appenzeller',
                       'bootarch' : 'x86_32',
                       'buildarchs' : ['x86_64', 'x86_32'],
                       'cores_per_socket': 12,
                       'perfcount_type': 'amd10',
                       'tickrate'    : 2200,
                       'boot_timeout': 360},

    'gottardo-32': {'ncores'      : 32,
                    'machine_name' : 'gottardo',
                    'bootarch' : 'x86_32',
                    'buildarchs' : ['x86_64', 'x86_32'],
                    'cores_per_socket': 16,
                    'perfcount_type': 'intel',
                    'tickrate'    : 1870,
                    'boot_timeout': 360},

    'westmere-32': {'ncores'      : 40,
                 'machine_name' : 'westmere',
                 'bootarch' : 'x86_32',
                 'buildarchs' : ['x86_64', 'x86_32'],
                 'cores_per_socket': 10,
                 'perfcount_type': 'intel',
                 'tickrate'    : 2394,
                 'boot_timeout': 360},
    }
