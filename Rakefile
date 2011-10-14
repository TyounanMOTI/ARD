require 'rake/loaders/makefile'

ENV['CC'] = "g++-4.6" if ENV['CC'].nil?
CC = ENV['CC']
ROOT_DIR = File.dirname(File.expand_path(__FILE__))
ENV['CCFLAGS'] = "-Wall -std=c++0x" if ENV['CCFLAGS'].nil?

GTEST_DIR = "#{ROOT_DIR}/gtest"
GTEST_INCLUDE_DIR = [GTEST_DIR, "#{GTEST_DIR}/include"]
GTEST_SRC = FileList.new() do |f|
  f.add "#{GTEST_DIR}/src/gtest_main.cc"
  f.add "#{GTEST_DIR}/src/gtest-all.cc"
end
GTEST_OBJS = GTEST_SRC.ext('o')

CUDA_INCLUDE_DIR = "/usr/local/cuda/include"
CUDA_LIB_DIR = "/usr/local/cuda/lib"

INCLUDE_DIRS = [GTEST_INCLUDE_DIR,
                CUDA_INCLUDE_DIR,
                ROOT_DIR,
                "/usr/local/include",
                "/usr/include",
                "/usr/local/Cellar/gcc/4.6.0/gcc/include/c++/4.6.0"
               ]
CCFLAGS = "#{ENV['CCFLAGS']} -I#{INCLUDE_DIRS.join(' -I')} -g"

BUILD_DIR = "#{ROOT_DIR}/build"
ARD_LIB = "#{BUILD_DIR}/libARD.a"

import "#{ROOT_DIR}/test/ARD_test.rake"
#import "2DVisualizer/2DVisualizer.rake"
#import "2DVisualizer/test/2DVisualizer_test.rake"

task :default => "ARD_test:run"

namespace "ARD" do
  current_dir = ROOT_DIR
  build_dir = BUILD_DIR
  srcs = FileList["#{current_dir}/*.cpp"]
  objs = srcs.pathmap("%{#{current_dir},#{build_dir}}X.o")
  shared_libs = ["cufft", "cudart", "fftw3", "fftw3f"]
  ccflags = CCFLAGS

  unless srcs.empty?
    file ARD_LIB => objs do |t|
      sh "#{CC} #{ccflags} -L#{CUDA_LIB_DIR} -l#{shared_libs.join(' -l')} -o #{t.name} #{t.prerequisites}"
      sh "ar -rv #{t.name} #{objs}"
    end
  end

  rule '.o' => "%{#{build_dir},#{current_dir}}X.cpp" do |t|
    directory BUILD_DIR
    sh "#{CC} #{ccflags} -c -o #{t.name} #{t.source}"
  end

  file "#{current_dir}/.depends.mf" => srcs do |t|
    sh "makedepend -f- -- #{ccflags} -- #{t.prerequisites.join(' ')} > #{t.name}"
  end

  import "#{current_dir}/.depends.mf"
end

namespace "gtest" do
  task :build => GTEST_OBJS

  rule '.o' => '.cc' do |t|
    sh "#{CC} #{CCFLAGS} -o #{t.name} -c #{t.source}"
  end
end

task :check_syntax do
  sh "#{CC} #{CCFLAGS} -fno-var-tracking -Wextra -fsyntax-only #{ENV["CHK_SOURCES"]}"
end
