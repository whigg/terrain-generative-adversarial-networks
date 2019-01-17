from parse_options import parse_args, print_args

class Inferencer :
    def __init__(self, options):
        pass

if __name__ == "__main__" :
    options = parse_args("inference")
    inferencer = Inferencer(options)