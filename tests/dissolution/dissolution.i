[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 25
  ny = 30
  nz = 0
  xmin = 0
  xmax = 5.0
  ymin = 0
  ymax = 6.0

  elem_type = QUAD4

  uniform_refine = 1
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
  active = 'pf_time pf_grad pf_loc pf_add pf_random
            conc_time conc_diffused conc_add conc_random'


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
    amplitude_alpha = 0.5
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
    amplitude_beta = 0.5
  [../]


[]


[BCs]

# Only left boundaries of phase field and concentration are needed and setup here
#  active = 'pf_bottom pf_top pf_right pf_left 
#            conc_bottom conc_top conc_right conc_left '   

   active = 'pf_left conc_left'

  [./pf_bottom]
     type = DirichletBC
     variable = pf
     boundary = 'bottom'
     value = -1.0
  [../]

  [./pf_top]
     type = DirichletBC
     variable = pf
     boundary = 'top'
     value = -1.0
  [../]

  [./pf_right]
     type = DirichletBC
     variable = pf
     boundary = 'right'
     value = -1.0
  [../]

  [./pf_left]
     type = DirichletBC
     variable = pf
     boundary = 'left'
     value = 1.0
  [../]


  [./conc_bottom]
     type = DirichletBC
     variable = conc
     boundary = 'bottom'
     value = 0.0
  [../]

  [./conc_top]
     type = DirichletBC
     variable = conc
     boundary = 'top'
     value = 0.0
  [../]

  [./conc_right]
     type = DirichletBC
     variable = conc
     boundary = 'right'
     value = 0.0
  [../]

  [./conc_left]
     type = DirichletBC
     variable = conc
     boundary = 'left'
     value = -1.0
  [../]
 
[]

[Materials]
  active = 'phase_field concentration'

  [./phase_field]
    type = ACMaterials
    block = 0
    epsilon = 0.05
    lambda = 0.8
  [../]

  [./concentration]
    type = ConcMaterials
    block = 0
    diffusivity = 0.5
    k = 500000.0
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
  num_steps = 3    # should be 100 in the example 
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
  file_base = out_dissolution
  output_initial = true
  exodus = true

  [./console]
    type = Console
    perf_log = true
    linear_residuals = true
  [../]
[]


