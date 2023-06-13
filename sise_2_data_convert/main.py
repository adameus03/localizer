from train_data import generate_train_data
from test_data import generate_validation_set
# from visualize import visualize_original_system
from visualize import visual_systems_comparison

if __name__ == '__main__':
    # generate_train_data()
    # generate_validation_set("f8", "1p")
    # generate_validation_set("f8", "1z")
    # generate_validation_set("f8", "2p")
    # generate_validation_set("f8", "2z")
    # generate_validation_set("f8", "3p")
    # generate_validation_set("f8", "3z")
    # generate_validation_set("f10", "1p")
    # generate_validation_set("f10", "1z")
    # generate_validation_set("f10", "2p")
    # generate_validation_set("f10", "2z")
    # generate_validation_set("f10", "3p")
    # generate_validation_set("f10", "3z")
    # generate_validation_set("f8", "random_1p")
    # generate_validation_set("f8", "random_2p")
    # generate_validation_set("f10", "random_1p")
    # generate_validation_set("f10", "random_2p")

    visual_systems_comparison("f8", "1p")
    visual_systems_comparison("f8", "1z")
    visual_systems_comparison("f8", "2p")
    visual_systems_comparison("f8", "2z")
    visual_systems_comparison("f8", "3p")
    visual_systems_comparison("f8", "3z")
    visual_systems_comparison("f10", "1p")
    visual_systems_comparison("f10", "1z")
    visual_systems_comparison("f10", "2p")
    visual_systems_comparison("f10", "2z")
    visual_systems_comparison("f10", "3p")
    visual_systems_comparison("f10", "3z")
    visual_systems_comparison("f8", "random_1p")
    visual_systems_comparison("f8", "random_2p")
    visual_systems_comparison("f10", "random_1p")
    visual_systems_comparison("f10", "random_2p")


