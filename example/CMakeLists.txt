set(example_SRCS
	example_server.cpp
)

add_executable(example
	${example_SRCS}
)

target_link_libraries(example
	iec60870
)
