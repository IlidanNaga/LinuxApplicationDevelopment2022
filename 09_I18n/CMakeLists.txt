cmake_minimum_required(VERSION 3.11)
project(guesser C)
set(CMAKE_C_STANDARD 99)

add_definitions(-DLOCALE_PATH="${PROJECT_SOURCE_DIR}/po")

add_executable(guesser guesser.c)

find_package(Gettext)


set(GETTEXT_DOMAIN ${CMAKE_PROJECT_NAME})
set(POT_FILE ${CMAKE_CURRENT_BINARY_DIR}/po/${GETTEXT_DOMAIN}.pot)

add_definitions(-DLOCALE_PATH="${PROJECT_SOURCE_DIR}/po")
add_definitions(-DGETTEXT_DOMAIN="${GETTEXT_DOMAIN}")

file(GLOB_RECURSE POT_SOURCES ${PROJECT_SOURCE_DIR}/*.c)

add_custom_target(format
    COMMAND clang-format -i guesser.c
    )
add_dependencies(guesser format)

add_custom_target(${GETTEXT_DOMAIN}-pot
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/po
    COMMENT "Generating fresh ${GETTEXT_DOMAIN}.pot file from sources"
    COMMAND xgettext --from-code=UTF-8 --keyword=_ --add-comments --output=${POT_FILE} ${POT_SOURCES}
    )

add_custom_target(init-translation DEPENDS ${GETTEXT_DOMAIN}-pot
    COMMENT "Generating empty .po files"
    COMMAND  msginit --no-translator -i ${POT_FILE} -l en_EN -o ${CMAKE_SOURCE_DIR}/po/en.po 
    COMMAND  msginit --no-translator -i ${POT_FILE} -l ru_RU -o ${CMAKE_SOURCE_DIR}/po/ru.po 
    )

add_custom_target(update-translation DEPENDS ${GETTEXT_DOMAIN}-pot
    COMMENT "Updating .po from fresh .pot"
    COMMAND msgmerge -U ${CMAKE_SOURCE_DIR}/po/ru.po ${POT_FILE}
    COMMAND msgmerge -U ${CMAKE_SOURCE_DIR}/po/en.po ${POT_FILE}
    )

add_custom_target(translate
    COMMENT "Compiling translation"
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/po/ru_RU/LC_MESSAGES
    COMMAND msgfmt -o ${CMAKE_CURRENT_BINARY_DIR}/po/ru_RU/LC_MESSAGES/${GETTEXT_DOMAIN}.mo ${CMAKE_SOURCE_DIR}/po/ru.po
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/po/en_EN/LC_MESSAGES
    COMMAND msgfmt -o ${CMAKE_CURRENT_BINARY_DIR}/po/en_EN/LC_MESSAGES/${GETTEXT_DOMAIN}.mo ${CMAKE_SOURCE_DIR}/po/en.po
    )

add_custom_target(git-clean
    COMMAND git clean -fd ${CMAKE_SOURCE_DIR}
    )

add_dependencies(guesser translate)
