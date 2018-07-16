
cxx_library(
  name = 'allocate_lib',
  header_namespace = 'allocate',
  exported_headers = subdir_glob([
    ('include', '**/*.hpp'),
  ]),
  srcs = glob([
    'source/*.cpp'
  ]),
  exported_deps = [
    '//externals:SQLiteCpp'
  ],
  compiler_flags = [
    '-std=c++17',
  ],
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
    '-std=c++17',
  ],
  deps = [
    '//externals/framework:framework',
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
    '//externals/Catch2:Catch2'
  ],
  compiler_flags = [
    '-std=c++17',
  ],
)
