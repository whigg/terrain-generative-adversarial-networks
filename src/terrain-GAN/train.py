from parse_options import parse_args, print_args

class Trainer :
    def __init__(self, options):
        pass

if __name__ == "__main__" :
    options = parse_args("train")
    if options.args_verbose == True:
        print_args(options)

    gan_trainer = Trainer(options)