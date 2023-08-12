file (GLOB HEADERS "*.h")
file (GLOB SOURCES "[^_]*.cpp")

set(LIBRARY tex)
add_library(${LIBRARY} STATIC ${SOURCES})
set_property(TARGET ${LIBRARY} PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
# add_dependencies(${LIBRARY} ext_mve ext_rayint)
target_link_libraries(${LIBRARY} -ltbb -lmve ${PNG_LIBRARIES})
# install(TARGETS ${LIBRARY} ARCHIVE DESTINATION lib)
