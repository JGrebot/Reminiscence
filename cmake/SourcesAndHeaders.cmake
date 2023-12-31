set(sources
    src/question.cpp
    src/dailytask.cpp
)

set(exe_sources
    app/main.cpp
	${sources}
)

# quickstart.cpp is the rapidyml example file.
# set(exe_sources_2
#     app/quickstart.cpp
# 	${sources}
# )

set(headers
    include/question.hpp
    include/dailytask.hpp
    include/parser.hpp
)

set(test_sources
  src/hello.cpp
)
