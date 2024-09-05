
if(CMAKE_SKIP_INSTALL_RULES)
  include(cmake/PackageProject.cmake)

    # Add other targets that you want installed here, by default we just package the one executable
    # we know we want to ship
    winxd_package_project(
      TARGETS
      WinXD
      winxd_options
      winxd_warnings
      # FIXME: this does not work! CK
      # PRIVATE_DEPENDENCIES_CONFIGURED project_options project_warnings
    )

    # Experience shows that explicit package naming can help make it easier to sort
    # out potential ABI related issues before they start, while helping you
    # track a build to a specific GIT SHA
    set(CPACK_PACKAGE_FILE_NAME
        "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
    )

    include(CPack)
endif()

