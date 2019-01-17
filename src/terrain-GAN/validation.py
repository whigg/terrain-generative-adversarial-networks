from parse_options import parse_args, print_args

class Validation :
    def __init__(self, options):
        pass

if __name__ == "__main__" :
    options = parse_args("validation")
    if options.args_verbose == True:
        print_args(options)

    gan_validation = Validation(options)