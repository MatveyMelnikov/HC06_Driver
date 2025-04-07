# File for test cases
# Here you can add platform-specific files (main file, test, etc.)

CFLAGS = -DTEST -DUNITY_INCLUDE_CONFIG_H
TESTS_DIR = Tests
UNITY_DIR = External/Unity-2.5.2
HC06_DRIVER = External/HC06_Driver
BUILDER_HC06_DRIVER = External/Builder_HC06_Driver
FOR_TARGET = Y

C_INCLUDES += \
-I$(HC06_DRIVER)/Inc \
-I$(UNITY_DIR)/src \
-I$(UNITY_DIR)/extras/fixture/src \
-I$(UNITY_DIR)/extras/memory/src \
-I$(TESTS_DIR)

C_SOURCES += \
$(HC06_DRIVER)/Src/hc06_driver.c \
$(UNITY_DIR)/src/unity.c \
$(UNITY_DIR)/extras/fixture/src/unity_fixture.c \
$(UNITY_DIR)/extras/memory/src/unity_memory.c

ifeq ($(FOR_TARGET), Y)
C_INCLUDES += \
-I$(BUILDER_HC06_DRIVER)/Inc
C_SOURCES += \
$(TESTS_DIR)/target_tests.c \
$(TESTS_DIR)/target_tests/hc06_driver/hc06_test_runner.c \
$(TESTS_DIR)/target_tests/hc06_driver/hc06_test.c \
$(BUILDER_HC06_DRIVER)/Src/builder_hc06_driver.c

include MakefileTestTarget.mk
else
C_INCLUDES += \
-I$(TESTS_DIR)/mocks/Inc \
-I$(TESTS_DIR)/fakes/Inc
C_SOURCES += \
$(TESTS_DIR)/host_tests.c \
$(TESTS_DIR)/host_tests/hc06_driver/hc06_test_runner.c \
$(TESTS_DIR)/host_tests/hc06_driver/hc06_test.c \
$(TESTS_DIR)/mocks/Src/mock_delay.c \
$(TESTS_DIR)/mocks/Src/mock_uart.c \
$(TESTS_DIR)/mocks/Src/mock.c

include MakefileTestHost.mk
endif
