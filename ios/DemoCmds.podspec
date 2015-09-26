Pod::Spec.new do |s|
  s.name        = "DemoCmds"
  s.version     = "0.0.1"
  s.summary     = "A template and example project containing customized shape and command classes."
  s.homepage    = "https://github.com/rhcad/DemoCmds"
  #s.license     = { :type => "LGPL", :file => "LICENSE.md" }
  s.author      = { "Zhang Yungui" => "rhcad@hotmail.com" }

  s.platform    = :ios, "6.0"
  s.source      = { :git => "https://github.com/rhcad/DemoCmds.git", :branch => "master" }
  s.source_files  = "core", "core/**/*.{h,cpp}"
  #s.exclude_files = "ios/DemoCmds/DemoCmds"
  s.public_header_files = "core/gate/*.h"
  #s.frameworks = "Foundation"

  s.requires_arc = true
  s.xcconfig = {
    'CLANG_CXX_LANGUAGE_STANDARD' => 'gnu++11',
    'CLANG_CXX_LIBRARY' => 'libc++',
    "HEADER_SEARCH_PATHS" => '$(PODS_ROOT)/Headers/TouchVGCore'
  }
  s.dependency "TouchVGCore"
end
