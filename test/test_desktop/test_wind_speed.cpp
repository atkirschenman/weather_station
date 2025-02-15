/*
 Copyright (c) 2014-present PlatformIO <contact@platformio.org>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
**/

#include <unity.h>
#include "wind_speed.hpp"

WindSpeed windSpeed(2);

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_queue()
{
    windSpeed.mock_handle_interupt(500);
    windSpeed.mock_handle_interupt(1000);
    windSpeed.mock_handle_interupt(1500);
    TEST_ASSERT_EQUAL(60, windSpeed.get_wind_speed());
}

int main(int argc, char** argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_queue);
    UNITY_END();

    return 0;
}