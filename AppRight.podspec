Pod::Spec.new do |s|
  s.name         = "AppRight"
  s.version      = "2.2.0"
  s.summary      = "AppRight gathers information on the core performance metrics that matter most to application users."
  s.homepage     = "https://github.com/BugsterIO/BugsterIO-iOS"

  s.license      = { :type => 'Commercial', :file => 'LICENSE' }

  s.platform     = :ios, '6.0'
  s.author       = { "Gryphonet" => "contact@gryphonet.com" }
  s.source       = { :git => "https://github.com/rmishyn/AppRight.git", :tag => s.version.to_s }
  s.source_files = 'AppRight.framework/Headers/*.h'
  s.preserve_paths = 'AppRight.framework/AppRight'
  s.library      = 'AppRight'
  
  s.xcconfig = { 'LIBRARY_SEARCH_PATHS' => '$(PODS_ROOT)/AppRight/' }

  s.frameworks = 'Foundation', 'SystemConfiguration', 'CoreData', 'MessageUI'
  
end