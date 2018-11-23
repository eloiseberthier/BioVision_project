# psc_biovision
A project involving 5 students from the École polytechnique and the Thales Group on artificial vision. It is quite a high level idea of a system, but I think it contains some useful ideas, all of them inspired by Gestalt theory. We provide a C++ implementation on a simple Turtlebot robot, using the firmware ROS. It may not be directly usable as such, as I think some of the ROS nodes are missing (at least the feature extractor).

The idea is to model a 'context' using visual informations, and to propose a simple algorithm to discriminate between contexts. We consider a small robot with a camera, which moves in some different places.

In real time, it receives visual informations from its camera. For each image, we only collect a feature vector (in dimension 512 for instance), extracted from the initial image (on the retina) by a pretrained ConvNet (on ImageNet). Thus we (kind of) model the higher level information sent from the visual cortex to the rest of the brain.

Instead of just using these visual informations to classify objects, we send them to a self organizing map (SOM or Kohonen map), which models a kind of central system or memory. It allows to represent all the visual information along time t on a low dimension space (a 2 or 3d discrete map of points in dimension 512, see the definition of a SOM).

This map evolves over time, as it receives various visual information from various contexts. We suppose the visual information from two different contexts (like an office vs a bedroom) are somehow different in dimension 512, because they are composed by different objects, and generally they generate a different 'intuitive' visual impression. So one can hope that information from different contexts will activate different places on the map, and finally different regions of the map will represent different contexts. The choice of a SOM is again bio-inspired.

Over time, the robots successively sees several times several contexts, for which we can give it a label or not. Note that in this system, the time cannot be inverted, so it conforms with the way babies gradually discover the world. When the robot gets in a new room, either the context is known, and the visual information will activate a well-known region of the map and it will recognize a known context. Either it is unknown, and it will reshape a new region of the map to model this new context.

It is not clear which degree of supervision we should give. The mapping from visual informations to the SOM is unsupervised, up to a proper setting of the parameters (the shape of the map). Then recognizing a context from an activation of the map could be either a supervised or an unsupervised task.

We made some not very conclusive first experiments, but did not have enough time to lead them properly. I'll try to find some time to make them some day. Some of the choices we made can be retrospectively considered naive, but at this time none of us knew much about computer vision.
