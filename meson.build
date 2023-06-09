project('GCP_GSA', 'c',
        version : '0.1')

add_global_arguments('-O3',
                     language : 'c') #-g

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)
glib = dependency('glib-2.0')
thread_dep = dependency('threads')

src = [
  'src/main.c',
  'src/input_parser.c',
  'src/gcp.c',
  'src/gsa.c',
  'src/agent.c',
  'src/color.c',
  'src/graph.c',
  'src/vector.c'
]

includes = include_directories('src/')

TSP_SA = static_library('GCP_GSA', src,
                        dependencies: [ glib, m_dep, thread_dep ],
                        include_directories: [ includes ],
                        install : true)

exe = executable('GCP_GSA', src,
                 dependencies: [ glib, m_dep, thread_dep ],
                 install : true)
