
set (lib_client_SRCS
./server.cpp
./handlers.cpp
)


add_library (iec60870-shared SHARED ${lib_client_SRCS})
add_library (iec60870 STATIC ${lib_client_SRCS})

target_link_libraries(iec60870
libiec60870.so
-lm
-lpthread
)

target_link_libraries(iec60870-shared
libiec60870.so
)

set_target_properties(iec60870-shared PROPERTIES
           OUTPUT_NAME iec60870
           SOVERSION "${LIB_VERSION_MAJOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH}"
)

install (TARGETS iec60870 iec60870-shared
RUNTIME DESTINATION bin COMPONENT Applications
ARCHIVE DESTINATION lib COMPONENT Libraries
    LIBRARY DESTINATION lib COMPONENT Libraries
)

