/*<!--

 BSD 3-Clause License

  Copyright (c) 2020 Okinawa Institute of Science and Technology (OIST).
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following
     disclaimer in the documentation and/or other materials provided
     with the distribution.
   * Neither the name of Willow Garage, Inc. nor the names of its
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

 Author: Hendry F. Chame <hendryfchame@gmail.com>

 Publication:

   "Towards hybrid primary intersubjectivity: a neural robotics
   library for human science"

   Hendry F. Chame, Ahmadreza Ahmadi, Jun Tani

   Okinawa Institute of Science and Technology Graduate University (OIST)
   Cognitive Neurorobotics Research Unit (CNRU)
   1919-1, Tancha, Onna, Kunigami District, Okinawa 904-0495, Japan

-->*/


#ifndef SRC_CONTEXT_PVRNN_H_
#define SRC_CONTEXT_PVRNN_H_

#include "../includes.h"
#include "IContext.h"

namespace oist {

/**
 * This class implements a PV-RNN context buffer.
 * It basically functions as a data structure to read/write shared information among
 * PV-RNN layers within the network.
 * */
class ContextPvrnn : public IContext {

public:

	// forward computation

	VectorXf dp_bottom_prev; 	//!< Latent state *d* (prior distribution) from the bottom layer, for time step *t-1*
	VectorXf dq_bottom_prev; 	//!< Latent state *d* (posterior distribution) from the bottom layer, for time step *t-1*
	VectorXf dp_top_prev;    	//!< Latent state *d* (prior distribution) from the bottom layer, for time step *t-1*
	VectorXf dq_top_prev;    	//!< Latent state *d* (posterior distribution) from the bottom layer, for time step *t-1*

	// backward computation

	VectorXf g_h_next;		  	//!< Gradient for latent state *h* (posterior distribution) for time step *t+1*
	VectorXf g_hq_bottom_next;	//!< Gradient for latent state *h* (posterior distribution) from the bottom layer, for time step *t+1*
	VectorXf g_hq_top_next;	  	//!< Gradient for latent state *h* (posterior distribution) from the top layer, for time step *t+1*
	VectorXf g_dqloss;		  	//!< Gradient for latent state *d* (posterior distribution), for time step *t*

	ArrayXf dp_gen;			 	//!< Latent state *d* (prior distribution), for time step *t*

	// ------------ training mode

	arrayXf2DContainer t_dp;	//!< Training mode: latent state *d* (prior distribution), for time step *t*
	arrayXf2DContainer t_dq;	//!< Training mode: latent state *d* (posterior distribution), for time step *t*
	float2DContainer t_kld;		//!< Training mode: regulation term (KL-divergence), for time step *t*

	// ------------ Experiment mode

	arrayXf1DContainer e_dp; 	//!< Experiment mode: latent state *d* (prior distribution), for time step *t*
	arrayXf1DContainer e_dq; 	//!< Experiment mode: latent state *d* (posterior distribution), for time step *t*
	float1DContainer e_kld;		//!< Experiment mode: regulation term (KL-divergence), for time step *t*

	// Methods

	/**
	 * Constructor
	 * */
	ContextPvrnn();

	/**
	 * Gets the derived (non-abstract) class name
	 * @return: Derived class name
	 * */
	string getClassName();

	/**
	 * Shows the context state in the standard output
	 * */
	void print();

	/**
	 * Destructor
	 * */
	~ContextPvrnn();

};

} /* namespace oist */

#endif /* SRC_CONTEXT_PVRNN_H_ */
