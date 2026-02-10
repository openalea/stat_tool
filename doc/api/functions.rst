Functions
=========

.. doxygenfunction:: cumul_computation(int nb_value, const double *pmass, double *pcumul)
.. doxygenfunction:: cumul_distance_computation(int dim, double *distance)
.. doxygenfunction:: pattern_sort(int nb_pattern, double *distance, int nb_sorted_pattern)
.. doxygenfunction:: von_mises_concentration_computation
.. doxygenfunction:: q_q_plot_computation(double min_value, double step, int nb_step, double *theoretical_cdf, int nb_value, double **empirical_cdf)
.. doxygenfunction:: q_q_plot_computation(int nb_value, double **cdf) const
.. doxygenfunction:: q_q_plot_print(const char *path, int nb_value, double **qqplot)
.. doxygenfunction:: q_q_plotable_write(SinglePlot &plot, int nb_value, double **qqplot)
.. doxygenfunction:: cumul_matching_plot_print
.. doxygenfunction:: set_seed
.. doxygenfunction:: column_width(double min_value, double max_value)
.. doxygenfunction:: column_width(int min_value, int max_value)
.. doxygenfunction:: column_width(int nb_value, const double *value, double scale)
.. doxygenfunction:: column_width(int value)
.. doxygenfunction:: plot_print(const char *path)
.. doxygenfunction:: plot_print(const char *path) const
.. doxygenfunction:: plot_print(const char *path, const FrequencyDistribution *histo = NULL) const
.. doxygenfunction:: plot_print(const char *path, const Histogram *histo1 = NULL, const FrequencyDistribution *histo2 = NULL)
.. doxygenfunction:: plot_print(const char *path, double *concentration, double scale) const
.. doxygenfunction:: plot_print(const char *path, double *cumul, double *concentration, double shift = 0.) const
.. doxygenfunction:: plot_print(const char *path, double *standard_residual = NULL) const
.. doxygenfunction:: plot_print(const char *path, int ilength = I_DEFAULT, const Curves *curves_0 = NULL, const Curves *curves_1 = NULL) const
.. doxygenfunction:: plot_print(const char *path, int nb_dist, const Distribution **dist, double *scale, int *dist_nb_value, int nb_histo, const FrequencyDistribution **histo)
.. doxygenfunction:: plot_print(const char *path, int nb_dist, const Distribution **dist, double *scale, int *dist_nb_value, int nb_histo, const FrequencyDistribution **histo)
.. doxygenfunction:: plot_print(const char *path, int nb_histo = 0, const FrequencyDistribution **histo = NULL) const
.. doxygenfunction:: plot_print(const char *prefix, const char *title, int process, FrequencyDistribution **empirical_observation = NULL, FrequencyDistribution *marginal_distribution = NULL, model_type model = HIDDEN_MARKOV) const
.. doxygenfunction:: plot_print(const char *prefix, const char *title, int process, FrequencyDistribution **empirical_observation = NULL, FrequencyDistribution *marginal_distribution = NULL, model_type model = HIDDEN_MARKOV) const
.. doxygenfunction:: plot_print(const char *prefix, const char *title, int process, Histogram **observation_histogram = NULL, FrequencyDistribution **observation_distribution = NULL, Histogram *marginal_histogram = NULL, FrequencyDistribution *marginal_distribution = NULL, int nb_value = I_DEFAULT, double **empirical_cdf = NULL, model_type model = HIDDEN_MARKOV) const
.. doxygenfunction:: log_computation(int nb_value, const double *pmass, double *plog)
.. doxygenfunction:: cumul_method
