#!/usr/bin/env python
# Software License Agreement (BSD License)
#
# Copyright (c) 2008, Willow Garage, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Revision $Id$

## Simple talker demo that listens to std_msgs/Strings published 
## to the 'chatter' topic

import roslib
roslib.load_manifest('std_msgs')
import numpy
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap
import rospy
import std_msgs.msg
from std_msgs.msg import String
from std_msgs.msg import Float64MultiArray


## Helper class to convert numpy matrix lists to and from a Float64MultiArray message object. 
class MultiArrayConverter():
   
  ## Take a Float64 MultiArray message, convert it into a list of numpy matrices
  def multiArrayToMatrixList(self, ma_msg):
    dim = len(ma_msg.layout.dim)
    offset = ma_msg.layout.data_offset
    
    if dim != 3:
      print "Error: Must be 3 dimensions"
    
    #if (ma_msg.layout.dim[0].label != "matrix"):
    #  print "Error: dim[0] should be the matrices"
    #num_matrices = ma_msg.layout.dim[0].size
    
    if (ma_msg.layout.dim[0].label != "row"):
      print "Error: dim[1] should be the rows"
    rows = ma_msg.layout.dim[0].size
    
    if (ma_msg.layout.dim[1].label != "column"):
      print "Error: dim[2] should be the columns"
    columns = ma_msg.layout.dim[1].size
    
    ## Initialise empty matrix based on number of row/columns.
    #
    # NB: THIS IS ASSUMED TO BE CONSTANT FOR A GIVEN MESSAGE (or the multiarray structure breaks)
    mat = numpy.matrix(numpy.empty([rows,columns]))
    mat.fill(numpy.nan)
    
    #matrix_list = [mat]*num_matrices
    
    for j in range(0, rows):
      for k in range(0, columns):
        #matrix = matrix_list[i]
        data_index = ma_msg.layout.data_offset + (columns) * j + k
        mat[j,k] = ma_msg.data[data_index] 
    
    return mat
    
    
  ## Convert a list of 2D numpy matrices to a Float64MultiArray message
  #
  # Assumption: Each numpy matrix must be the same size (rows, columns)
  def matrixListToMultiarray(self, matrix_list):
    num_matrices = len(matrix_list)
    if num_matrices > 0:
      rows, columns = matrix_list[0].shape
    else:
      rows = 0
      columns = 0
    
    msg = std_msgs.msg.Float64MultiArray()
    
    # Set up layout
    msg.layout.data_offset = 0
    
    # Set up layout dimensions
    matrix_dim = std_msgs.msg.MultiArrayDimension()
    matrix_dim.label = "matrix"
    matrix_dim.size = num_matrices
    matrix_dim.stride = columns * rows * num_matrices
    
    row_dim = std_msgs.msg.MultiArrayDimension()
    row_dim.label = "row"
    row_dim.size = rows
    row_dim.stride = columns * rows
    
    col_dim = std_msgs.msg.MultiArrayDimension()
    col_dim.label = "column"
    col_dim.size = columns
    col_dim.stride = columns
    
    msg.layout.dim = [matrix_dim, row_dim, col_dim]
    
    # Copy data from matrices into the msg data block
    msg_data = [float('NaN')] * (msg.layout.data_offset + num_matrices * rows * columns)
    
    for i in range(0, num_matrices):
      for j in range(0, rows):
        for k in range(0, columns):
          matrix = matrix_list[i]
          data_index = msg.layout.data_offset + (rows*columns) * i + (columns) * j + k
          msg_data[data_index] = matrix[j,k]
          
    msg.data = msg_data
    
    return msg



def heat_callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)
    msg=MultiArrayConverter.multiArrayToMatrixList(converter, data)
    print(msg)
#    matrix=msg[0]
#    print(matrix)
#    x = numpy.arange(0, 40, 1)
#    y = numpy.arange(0, 30, 1)
#    X, Y = numpy.meshgrid(x, y)
    Z = msg
    colors = [(0, 0, 1), (1, 1, 0), (1, 0, 0)]  # B -> Y -> R
    cmap_name = 'my_list'
    cm = LinearSegmentedColormap.from_list(cmap_name, colors, N=50)
    im = plt.imshow(Z, interpolation='nearest', origin='lower', cmap=cm)
    plt.colorbar(im)
    plt.savefig('heat.png')
    plt.show(im)

def class_callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)
    P=data.data
    lbls=["context %s" %i for i in range(len(P))]
    labels=[lbls[i]+" : "+str(P[i]) for i in range(len(P))]
    plt.pie(P,labels=labels)
    plt.title('Contexts probabilities')
    plt.savefig('probas.png')
    plt.show()

def listener():
    rospy.init_node('listener', anonymous=True)
    
    #rospy.Subscriber('neural_n', Float64MultiArray, class_callback)
    rospy.Subscriber('heat_map', Float64MultiArray, heat_callback)
    #rospy.Subscriber('probs', Float64MultiArray, class_callback)
    
    rospy.spin()

if __name__ == '__main__':
    converter=MultiArrayConverter()
    listener()
