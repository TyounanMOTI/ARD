require 'rake/clean'

namespace "ARD_test" do
  current_dir = File.dirname(File.expand_path(__FILE__))
  build_dir = "#{current_dir}/build"
  lib_dirs = [CUDA_LIB_DIR]

  bin_file = "#{build_dir}/ARD_test"
  srcs = FileList.new("#{current_dir}/*.cpp") do |f|
    f.exclude(/.*microphone_test.cpp/)
    f.exclude("*_flymake.*")
  end
  objs = srcs.pathmap("%{#{current_dir},#{build_dir}}X.o")
  shared_libs = ["fftw3", "fftw3f", "cufft", "cudart"]
  static_libs = GTEST_OBJS
  if File.exists?(ARD_LIB)
    static_libs << ARD_LIB
  end

  CLEAN.include(objs)
  CLOBBER.include(bin_file)

  ccflags = CCFLAGS
  cc_libflags = "-L#{lib_dirs.join(' -L')} -l#{shared_libs.join(' -l')}"
  linker_flags = "-Xlinker -rpath -Xlinker #{CUDA_LIB_DIR}"

  task :run => bin_file do |t|
    sh "#{bin_file} --gtest_color=yes"
  end

  file bin_file => objs + static_libs do |t|
    sh "#{CC} #{ccflags} #{cc_libflags} #{linker_flags} -o #{t.name} #{t.prerequisites.join(' ')}"
  end

  rule '.o' => "%{#{build_dir},#{current_dir}}X.cpp" do |t|
    sh "#{CC} #{ccflags} -c -o #{t.name} #{t.source}"
  end

  file "#{current_dir}/.depends.mf" => srcs do |t|
    sh "makedepend -f- -- #{ccflags} -- #{t.prerequisites.join(' ')} > #{t.name}"
  end

  import "#{current_dir}/.depends.mf"
end
