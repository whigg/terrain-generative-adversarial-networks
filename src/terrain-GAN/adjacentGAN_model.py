from keras_contrib.layers.normalization import InstanceNormalization, BatchRenormalization
from keras.layers import Input, Dense, Reshape, Flatten, Dropout, Concatenate, Add, Conv2DTranspose
from keras.layers import BatchNormalization, Activation, ZeroPadding2D
from keras.layers.advanced_activations import ReLU, LeakyReLU
from keras.layers.convolutional import UpSampling2D, Conv2D
from keras.models import Sequential, Model
from keras.optimizers import Adam
from keras.engine.topology import Layer
from keras.engine import InputSpec
import tensorflow as tf

class ReflectionPadding2D(Layer):
    """
    from https://stackoverflow.com/questions/50677544/reflection-padding-conv2d
    """
    def __init__(self, padding=(1, 1), **kwargs):
        self.padding = tuple(padding)
        self.input_spec = [InputSpec(ndim=4)]
        super(ReflectionPadding2D, self).__init__(**kwargs)

    def get_output_shape_for(self, s):
        """ If you are using "channels_last" configuration"""
        return (s[0], s[1] + 2 * self.padding[0], s[2] + 2 * self.padding[1], s[3])

    def call(self, x, mask=None):
        w_pad,h_pad = self.padding
        return tf.pad(x, [[0,0], [h_pad,h_pad], [w_pad,w_pad], [0,0] ], 'REFLECT')

class AdjacentGAN :
    def __init__(self, name, width=1024, height=1024, input_channel=2, output_channel=1):
        self.name           = name
        self.width          = width
        self.height         = height
        self.input_channel  = input_channel
        self.output_channel = output_channel
        self.image_shape    = (self.width, self.height, self.input_channel)

        self.discriminator  = self._build_discriminator()
        self.generator      = self._build_generator()

    def _build_generator(self):
        def ck(layer_input, filters, f_size=7, i_norm=True) :
            d = ReflectionPadding2D(padding=(3, 3))(layer_input)
            d = Conv2D(filters, kernel_size=f_size, padding="valid")(d)
            if i_norm == True :
                d = InstanceNormalization()(d)
            d = ReLU()(d)
            return d
        def dk(layer_input, filters, f_size=3, i_norm=True) :
            d = Conv2D(filters, kernel_size=f_size, strides=2, padding="same")(layer_input)
            if i_norm == True :
                d = InstanceNormalization()(d)
            d = ReLU()(d)
            return d
        def Rk(layer_input, filters, f_size=3, i_norm = True) :
            d = ReflectionPadding2D(padding=(1, 1))(layer_input)
            d = Conv2D(filters, kernel_size=f_size, padding="valid")(d)

            if i_norm == True :
                d = InstanceNormalization()(d)
            d = ReLU()(d)
            d = ReflectionPadding2D(padding=(1, 1))(d)
            d = Conv2D(filters, kernel_size=f_size, padding="valid")(d)
            if i_norm == True :
                d = InstanceNormalization()(d)
            d = Add()([layer_input, d])
            d = ReLU()(d)
            return d
        def uk(layer_input, filters, f_size=3, i_norm=True) :
            d = Conv2DTranspose(filters, kernel_size=f_size, stride=2, padding="same", output_padding="same")(layer_input)
            if i_norm == True:
                d = InstanceNormalization()(d)
            d = ReLU()(d)
            return d
        gn_shape = (self.image_shape[0] / 2, self.image_shape[1] / 2, self.image_shape[2])

        g0 = Input(gn_shape)
        g1 = ck(g0, 64)
        g2 = dk(g1, 128)
        g3 = dk(g2, 256)
        g4 = dk(g3, 512)
        g5 = dk(g4, 1024)
        g6 = Rk(g5, 1024)
        g7 = Rk(g6, 1024)
        g8 = Rk(g7, 1024)
        g9 = Rk(g8, 1024)
        g10 = Rk(g9, 1024)
        g11 = Rk(g10, 1024)
        g12 = Rk(g11, 1024)
        g13 = Rk(g12, 1024)
        g14 = Rk(g13, 1024)
        g15 = uk(g14, 512)
        g16 = uk(g15, 256)
        g17 = uk(g16, 128)
        g18 = uk(g17, 64)

        gn_output = ck(g18, self.output_channel)
        global_network = Model(g0, gn_output)
        global_network.summary()

        l0 = Input(self.image_shape)
        l1 = ck(l0, 32)
        l2 = dk(l1, 64)
        l3 = Rk(l2, 64)
        l4 = Rk(l3, 64)
        l5 = Rk(l4, 64)
        l6 = uk(l5, 32)

        le_output = ck(l6, self.output_channel)
        local_enhancer = Model(l0, le_output)
        local_enhancer.summary()

        return [local_enhancer, global_network]

    def _build_discriminator(self):
        def Ck(input_layer, filters, f_size=4, i_norm=True) :
            d = Conv2D(filters, kernel_size=f_size, strides=2, padding="same")(input_layer)
            if i_norm == True:
                d = InstanceNormalization()(d)
            d = LeakyReLU(alpha=0.2)(d)
            return d

        d0 = Input(self.image_shape)
        d1 = Ck(d0, 64, i_norm=False)
        d2 = Ck(d1, 128)
        d3 = Ck(d2, 256)
        output_prediction = Ck(d3, 512)

        model = Model(d0, output_prediction)
        model.summary()

        return model


def createModel(mode="train") :
    """
    return dictionary which composed of generator and discriminators.
    :param mode: choice = ["train", "inference", "validation"]
    :return: { "G" : Generator, "D" : Discriminator }
    """
    model_dict = {"G" : None, "D" : None}
    if mode == "train" :
        pass
    elif mode == "inference" or mode == "test" :
        pass
    elif mode == "validation":
        pass
    else:
        raise Exception("Unexpected mode input")

    return model_dict

if __name__ == "__main__" :
    model = AdjacentGAN("AdjGAN")
