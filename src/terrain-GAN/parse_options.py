import argparse
import pprint
import os

def parse_args(mode = "train") :
    """
    parse arguments for given mode input.
    :param mode: choices ["train", "inference", "validation"]
    :return: arguments
    """
    parser = argparse.ArgumentParser()
    # common options
    parser.add_argument("--input_dir", default="./dataset", help="input dataset path")
    parser.add_argument("--output_dir", default="./output", help="output resources path")
    parser.add_argument("--checkpoint_dir", default="./checkpoint", help="checkpoint path where keras model's checkpoint will be saved at")
    parser.add_argument("--num_epochs", type=int)
    parser.add_argument("--batch_size", type=int)
    parser.add_argument("--output_type", default="png", choices=["png", "jpg"])

    if mode == "train" :
        parser.add_argument("--args_verbose", type=bool, default=True, help="whether print arguments or not")
        parser.add_argument("--mode", default="train")
    elif mode == "inference" or mode == "test" :
        parser.add_argument("--args_verbose", type=bool, default=False, help="whether print arguments or not")
        parser.add_argument("--mode", default="inference")
    elif mode == "validation" :
        parser.add_argument("--args_verbose", type=bool, default=True, help="whether print arguments or not")
        parser.add_argument("--mode", default="validation")
    else:
        raise Exception("Unexpected mode input. input must be one of following choices. ['train', 'test', 'inference', 'validation']")

    args = parser.parse_args()
    return args

def print_args(args) :
    abs_path    = os.path.abspath(os.curdir)
    input_dir   = os.path.join(abs_path, args.input_dir)
    output_dir  = os.path.join(abs_path, args.output_dir)
    args_string = """========list of parsed arguments======== 
    input  directory  : {}
    output directory  : {}
    mode              : {}
    number of epochs  : {}
    batch size        : {}
    output image type : {}
========================================""".format(input_dir, output_dir, args.mode, args.num_epochs, args.batch_size, args.output_type)

    print(args_string)