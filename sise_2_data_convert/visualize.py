import array
import math
# import numpy as np
import matplotlib.pyplot as plt


def visualize_system(inputs_path, outputs_path, room, mode):
    inputs = load_array(inputs_path)
    outputs = load_array(outputs_path)

    n = len(inputs) // 2

    errors = list(
        map(lambda i: math.sqrt((inputs[2 * i] - outputs[2 * i]) ** 2 + (inputs[2 * i + 1] - outputs[2 * i + 1]) ** 2),
            range(n)))

    errors.sort()

    plot_x = errors
    plot_y = list(map(lambda i: i / n, range(n)))
    # print(plot_x)
    # print(plot_y)

    # Create the plot
    plt.plot(plot_x, plot_y)

    # Add labels and title
    plt.xlabel('Error')
    plt.ylabel('CDF')
    plt.title(f"{room}_{mode}")

    # Show the plot
    plt.show()

    # plt.savefig(f".png")


def visual_systems_comparison(room, mode):
    pathed_visual_systems_comparison(
        f"inputs_{room}_{mode}.bin",
        f"outputs_{room}_{mode}.bin",
        f"C:\\Users\\amade\\Downloads\\localizer\\validation_input_data\\inputs_{room}_{mode}.bin",
        f"C:\\Users\\amade\\Downloads\\localizer\\validation_output_data\\outputs_{room}_{mode}.bin",
        room,
        mode
    )


def pathed_visual_systems_comparison(inputs_path_1, outputs_path_1, inputs_path_2, outputs_path_2, room, mode):
    inputs_1 = load_array(inputs_path_1)
    outputs_1 = load_array(outputs_path_1)
    inputs_2 = load_array(inputs_path_2)
    outputs_2 = load_array(outputs_path_2)

    n = len(inputs_1) // 2
    if len(inputs_2) // 2 != n:
        print(f"len(inputs_1) = {len(inputs_1)}")
        print(f"len(outputs_1) = {len(outputs_1)}")
        print(f"len(inputs_2) = {len(inputs_2)}")
        print(f"len(outputs_2) = {len(outputs_2)}")
        raise Exception("Different size warning. Comment to disable.")

    errors_1 = list(
        map(lambda i: math.sqrt((inputs_1[2 * i] - outputs_1[2 * i]) ** 2 +
                                (inputs_1[2 * i + 1] - outputs_1[2 * i + 1]) ** 2), range(n)))

    errors_2 = list(
        map(lambda i: math.sqrt((inputs_2[2 * i] - outputs_2[2 * i]) ** 2 +
                                (inputs_2[2 * i + 1] - outputs_2[2 * i + 1]) ** 2), range(n)))

    errors_1.sort()
    errors_2.sort()

    plot_x_1 = errors_1
    plot_y_1 = list(map(lambda i: i / n, range(n)))

    plot_x_2 = errors_2
    plot_y_2 = list(map(lambda i: i / n, range(n)))

    # print(plot_x)
    # print(plot_y)

    # Create the plots
    plt.plot(plot_x_1, plot_y_1, color='red', label='original')
    plt.plot(plot_x_2, plot_y_2, color='green', label='filtered')

    # Add labels and title
    plt.xlabel('Error')
    plt.ylabel('CDF')
    plt.title(f"{room}_{mode}")

    plt.legend()

    plt.savefig(f"comparison_{room}_{mode}.png")

    # Show the plot
    plt.show()


def visualize_original_system(room, mode):
    inputs_path = f"inputs_{room}_{mode}.bin"
    outputs_path = f"outputs_{room}_{mode}.bin"
    visualize_system(inputs_path, outputs_path, room, mode)


def visualize_corrected_system(room, mode):
    inputs_path = f"C:\\Users\\amade\\Downloads\\localizer\\validation_input_data\\inputs_{room}_{mode}.bin"
    outputs_path = f"C:\\Users\\amade\\Downloads\\localizer\\validation_output_data\\outputs_{room}_{mode}.bin"
    visualize_system(inputs_path, outputs_path, room, mode)


def load_array(path):
    # Open the file in binary mode
    with open(path, 'rb') as file:
        # Create an array of type 'd' (double) to hold the floating-point numbers
        doubles_array = array.array('d')

        # Read the contents of the file into the array
        doubles_array.fromfile(file, 64)

    return list(map(lambda x: convert_to_coordinate(x), doubles_array))


def convert_to_coordinate(x):
    return -1000.0*math.log(2.0/(1.0+x)-1.0)
