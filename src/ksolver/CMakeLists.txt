# In UNIX, set PROJECT_SOURCES using the following command
# find . | grep .cpp
# Delete the ./ at the beginning of each file with block selection (alt + shift in Visual Studio)
set(PROJECT_SOURCES
expression.cpp
operators/addition.cpp
)

# In UNIX, set PROJECT_HEADERS using the following command
# find . | grep .h
# Delete the ./ at the beginning of each file with block selection (alt + shift in Visual Studio)
set(PROJECT_HEADERS
expression.hpp
operator.hpp
operators/addition.hpp
operators.hpp
property.hpp
solver.hpp
number.hpp
)


# Add source to this project's executable.
add_library(ksolver ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_include_directories(ksolver PRIVATE ${CMAKE_CURRENT_LIST_DIR})