from helpers import *
import platform


OS = platform.system()

if OS == 'Windows':
    GLFW_INCLUDE = 'C:/SDK/glfw/include'
    GLFW_LIB = 'C:/SDK/glfw/x64/lib-mingw-w64'
    STB_INCLUDE = 'C:/SDK/stb'

EXCLUDED_SOURCES = ['PlatformEmscripten.cpp', 'Vector2D.cpp']


def main():
    builder = Builder()

    create_dir_if_not_exists('../Target')

    c = Command('g++')

    c.add_flag('I"../../../defGameEngine/Include"')
    c.add_flag('Wall')
    c.add_flag('pedantic')
    c.add_flag('std', 'c++20')
    c.add_flag('fms-extensions')
    c.add_flag('o')
    c.add_argument(f'../Target/Example')

    for source in get_files('../../../defGameEngine/Sources'):
        if source not in EXCLUDED_SOURCES:
            c.add_argument('../../../defGameEngine/Sources/' + source)

    for source in get_files('../../Sources'):
        c.add_argument('../../Sources/' + source)

    match OS:
        case 'Windows':
            c.add_flag(f'I"{STB_INCLUDE}"')
            c.add_flag(f'I"{GLFW_INCLUDE}"')
            c.add_flag(f'L"{GLFW_LIB}"')
            c.add_flag('lgdi32')
            c.add_flag('luser32')
            c.add_flag('lkernel32')
            c.add_flag('lopengl32')
            c.add_flag('lglfw3dll')
            c.add_flag('lglu32')
        case 'Linux':
            c.add_flag('lGL')
            c.add_flag('lGLU')
            c.add_flag('lglut')
            c.add_flag('lGLEW')
            c.add_flag('lglfw')
            c.add_flag('lX11')
            c.add_flag('lXxf86vm')
            c.add_flag('lXrandr')
            c.add_flag('lpthread')
            c.add_flag('lXi')
            c.add_flag('ldl')
            c.add_flag('lXinerama')
            c.add_flag('lXcursor')
            c.add_flag('lstb')
        case _:
            assert False, 'Not implemeneted for your OS, please send an issue'

    builder.add_command(c)

    builder.execute(True, True, True)

if __name__ == '__main__':
    main()
