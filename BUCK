
cxx_library(
  name = 'allocate_lib',
  header_namespace = 'allocate',
  exported_headers = subdir_glob([
    ('include', '**/*.hpp'),
  ]),
  srcs = glob([
    'source/*.cpp'
  ]),
  platform_compiler_flags = [
    ('.x86_64$', {'/EHsc'}),
  ],
  compiler_flags = [
    '/EHsc'
  ],
  deps = [
    '//externals/framework:framework',
  ]
)

cxx_binary(
  name = 'allocate',
  srcs = glob([
    'app/*.cpp',
  ]),
  linker_flags = [
    '-lpthread',
  ],
  compiler_flags = [
    '/EHsc'
  ],
  deps = [
    '//:allocate_lib',
  ],
)

cxx_binary(
  name = 'test',
  headers = subdir_glob([
    ('include', '**/*.hpp'),
  ]),
  srcs = glob([
    'test/*.cpp',
  ]),
  deps = [
    '//:allocate',
    '//externals:Catch2'
  ],
  compiler_flags = [
  ],
)
