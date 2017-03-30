[Mesh]
  file = rectangle.e
[]

[Variables]
  active = 'conc pf'

  [./conc]
    order = FIRST
    family = LAGRANGE
    initial_condition = 0
  [../]

  [./pf]
    order = THIRD
    family = HERMITE
    initial_condition = -1.0
  [../]

[]

[Kernels]
  active = 'pf_time pf_grad pf_loc pf_add pf_add pf_random
            conc_time conc_diffused conc_add conc_random
            conc_convection'


  [./pf_time]
    type = ACTimeDerivative
    variable = pf
    epsilon_name = E
    b_name = B
    kc_name = KC
    k_name = K
    diffusivity_name = D 
    lambda_name = L
    tau = 0.0
  [../]

  [./pf_grad]
    type = ACGrad
    variable = pf
    epsilon_name = E
  [../]

  [./pf_loc]
    type = ACLoc
    variable = pf
    lambda_name = L
    concentration = conc
  [../]

  [./pf_add]
    type = ACAdd
    variable = pf
    epsilon_name = E
  [../]

  [./pf_random]
    type = RandomNoise
    variable = pf
    amplitude_alpha = 1.0
  [../]

  [./conc_time]
    type = TimeDerivative
    variable = conc
  [../]

  [./conc_diffused]
    type = ConcDiffusion
    variable = conc
    diffusivity_name = D 
  [../]

  [./conc_add]
    type = ConcAdd
    variable = conc
    phase = pf
    b_name = B
    kc_name = KC
    k_name = K
    diffusivity_name = D 
  [../]

  [./conc_random]
    type = RandomNoiseConc
    variable = conc
    phase = pf
    amplitude_beta = 1.0
  [../]

  [./conc_convection]
    type = Convection
    variable = conc
    velocity = '100.0 0.0 0.0'
  [../]


[]


[BCs]

# Only left boundaries of phase field and concentration are needed and setup here
#    active = 'pf_bottom pf_top pf_right pf_left 
#              conc_bottom conc_top conc_right conc_left' 

# Point source is set as a sideset boundary 

  active = 'pf_node conc_node'   

  [./pf_bottom]
     type = DirichletBC
     variable = pf
     boundary = '3'
     value = -1.0
  [../]

  [./pf_top]
     type = DirichletBC
     variable = pf
     boundary = '1'
     value = -1.0
  [../]

  [./pf_right]
     type = DirichletBC
     variable = pf
     boundary = '4'
     value = -1.0
  [../]

  [./pf_left]
     type = DirichletBC
     variable = pf
     boundary = '2'
     value = -1.0
  [../]


  [./conc_bottom]
     type = DirichletBC
     variable = conc
     boundary = '3'
     value = 0.0
  [../]

  [./conc_top]
     type = DirichletBC
     variable = conc
     boundary = '1'
     value = 0.0
  [../]

  [./conc_right]
     type = DirichletBC
     variable = conc
     boundary = '4'
     value = 0.0
  [../]

  [./conc_left]
     type = DirichletBC
     variable = conc
     boundary = '2'
     value = 0.0
  [../]

  [./pf_node]
     type = DirichletBC
     variable = pf
     boundary = '1'
     value = 1.0
  [../]

  [./conc_node]
     type = DirichletBC
     variable = conc
     boundary = '1'
     value = -1.0
  [../]
[]

[Materials]
  active = 'phase_field concentration'

  [./phase_field]
    type = ACMaterials
    block = 1
    epsilon = 1.0
    lambda = 0.8 
  [../]

  [./concentration]
    type = ConcMaterials
    block = 1 
    diffusivity = 20.0
    k = 1000000.0
    kc = 1.0
    ce = 2.0
    ps = 2.7
  [../]

[]

[Executioner]
  type = Transient

#  scheme = 'bdf2'
#  scheme = explicit-euler

#  Preconditioned JFNK (default)
   solve_type = 'PJFNK'

    petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
    petsc_options_value = 'hypre boomeramg 101'

      l_max_its = 20
      l_tol = 1.0e-2

      nl_max_its = 20
      nl_rel_tol = 1.0e-4

  start_time = 0.0
  num_steps = 100
  dt = 0.01

#     [./Adaptivity]
#         initial_adaptivity = 1
#         error_estimator = LaplacianErrorEstimator
#         refine_fraction = 0.8
#         coarsen_fraction = 0.05
#         max_h_level = 2
#       [../]
[]

[Outputs]
  file_base = out_dissolution_point_convenction
  output_initial = true
  exodus = true

  [./console]
    type = Console
    perf_log = true
    linear_residuals = true
  [../]
[]


