// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#ifndef _MULTILOCUSGENOTYPESTATISTICS_H_
#define _MULTILOCUSGENOTYPESTATISTICS_H_

// From STL
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

#include <Bpp/Exceptions.h>

// From bpp-seq
#include <Bpp/Seq/DistanceMatrix.h>

// From bpp-popgen
#include "PolymorphismMultiGContainer.h"
#include "MultilocusGenotype.h"
#include "GeneralExceptions.h"

namespace bpp
{
/**
 * @brief The MultilocusGenotypeStatistics class
 *
 * This class is a set of static method for PolymorphismMultiGContainer.
 *
 * @author Sylvain Gaillard
 */
class MultilocusGenotypeStatistics
{
public:
  struct VarComp
  {
    double a;
    double b;
    double c;
  };

  struct Fstats
  {
    double Fit;
    double Fst;
    double Fis;
  };

  struct PermResults
  {
    double statistic;
    double percentSup;
    double percentInf;
  };

  /**
   * @brief Get the alleles' id at one locus for a set of groups.
   *
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   */
  static std::vector<size_t> getAllelesIdsForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Count the number of allele (gametes) at a locus for a set of groups.
   *
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   */
  static size_t countGametesForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Get a map of allele count for a set of groups.
   *
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   */
  static std::map<size_t, size_t> getAllelesMapForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Get the alleles frequencies at one locus for a set of groups.
   *
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   * @throw ZeroDivisionException if the number of considered alleles = 0.
   */
  static std::map<size_t, double> getAllelesFrqForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Count the number of non-missing data at a given locus for a set of groups.
   *
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   */
  static size_t countNonMissingForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Counr the number of bi-allelic MonolocusGenotype at a given locus for a set of groups.
   *
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   */
  static size_t countBiAllelicForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Count how many times each allele is found in an heterozygous MonolocusGenotype in a set of groups.
   *
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   */
  static std::map<size_t, size_t> countHeterozygousForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Get the heterozygous frequencies for each allele at a locus in a set of groups.
   *
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   * @throw ZeroDivisionException if the number of considered alleles = 0.
   */
  static std::map<size_t, double> getHeterozygousFrqForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the observed heterozygosity for one locus.
   *
   * This is the mean value of the getHeterozygousFrqForGroups map.
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   * @throw ZeroDivisionException if the number of considered alleles = 0.
   */
  static double getHobsForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the expected heterozygosity for one locus.
   *
   * Nei 1977
   * @f[
   * H_{exp}=1-\sum_{i=1}^{n}x_i^2
   * @f]
   * where @f$x_i@f$ is the frequency of the i<sup>th</sup> allele and @f$n@f$ the number of alleles.
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   * @throw ZeroDivisionException if the number of considered alleles = 0.
   */
  static double getHexpForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the expected non biased heterozygosity for one locus.
   *
   * Nei 1978
   * @f[
   * H_{nb}=\frac{2n}{2n-1}\left(1-\sum_{i=1}^{n}x_i^2\right)=\frac{2n}{2n-1}H_{exp}
   * @f]
   * where @f$x_i@f$ is the frequency of the i<sup>th</sup> allele and @f$n@f$ the number of alleles.
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   * @throw ZeroDivisionException if the number of considered alleles = 0.
   */
  static double getHnbForGroups(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the Nei distance between two groups at one locus.
   *
   * Nei 1972
   * @f[
   * \hat{D}_1=-\ln \left[\frac{\displaystyle\sum_{i=1}^{n}\left(x_i\times y_i\right)}
   * {\sqrt{\displaystyle\sum_{i=1}^{n}x_i^2\times \displaystyle\sum_{i=1}^{n}y_i^2}}\right]
   * @f]
   * where @f$x_i@f$ and @f$y_i@f$ are respectively the i<sup>th</sup> allele's frequency of the first and second group
   * and @f$n@f$ the total number of alleles of both groups.
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   * @throw ZeroDivisionException if the number of considered alleles = 0.
   */
  static double getDnei72(
      const PolymorphismMultiGContainer& pmgc,
      std::vector<size_t> locusPositions,
      size_t grp1,
      size_t grp2);

  /**
   * @brief Compute the Nei unbiased distance between two groups at a given number of loci.
   *
   * Nei 1978
   * @f[
   * \hat{D}=-\ln \left[\frac{\displaystyle\sum_{i=1}^{n}\left(x_i\times y_i\right)}
   * {\sqrt{\frac{2n_XJ_X-1}{2n_X-1}\times\frac{2n_YJ_Y-1}{2n_YJ_Y}}}
   * \right]
   * @f]
   * where @f$x_i@f$ and @f$y_i@f$ are respectively the i<sup>th</sup> allele's frequency of the first and second group,
   * @f$n@f$ the total number of alleles of both groups, @f$n_X@f$ and @f$n_Y@f$ the number of alleles in the first and second group
   * and
   * @f[
   * J_X=\sum_{i=1}^{n}x_i^2
   * \qquad\textrm{and}\qquad
   * J_Y=\sum_{i=1}^{n}y_i^2
   * @f]
   * @throw IndexOutOfBoundsException if locusPosition excedes the number of loci of one MultilocusGenotype.
   * @throw ZeroDivisionException if the number of considered alleles = 0.
   */
  static double getDnei78(
      const PolymorphismMultiGContainer& pmgc,
      std::vector<size_t> locusPositions,
      size_t grp1,
      size_t grp2);

  /**
   * @brief Compute the three F statistics of Weir and Cockerham for each allele of a given locus.
   */
  static std::map<size_t, Fstats> getAllelesFstats(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the Weir and Cockerham Fit on a set of groups for each allele of a given locus.
   */
  static std::map<size_t, double> getAllelesFit(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the Weir and Cockerham @f$\theta@f$ on a set of groups for each allele of a given locus.
   */
  static std::map<size_t, double> getAllelesFst(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the Weir and Cockerham Fis on a set of groups for each allele of a given locus.
   */
  static std::map<size_t, double> getAllelesFis(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Get the variance components a, b and c (Weir and Cockerham, 1983).
   */
  static std::map<size_t, VarComp> getVarianceComponents(
      const PolymorphismMultiGContainer& pmgc,
      size_t locusPosition,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the Weir and Cockerham @f$\theta{wc}@f$ on a set of groups for a given set of loci.
   * The variance componenets for each allele are calculated and then combined over loci using Weir and Cockerham weighting.
   */
  static double getWCMultilocusFst(
      const PolymorphismMultiGContainer& pmgc,
      std::vector<size_t> locusPositions,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the Weir and Cockerham Fis on a set of groups for a given set of loci.
   * The variance componenets for each allele are calculated and then combined over loci using Weir and Cockerham weighting.
   */
  static double getWCMultilocusFis(
      const PolymorphismMultiGContainer& pmgc,
      std::vector<size_t> locusPositions,
      const std::set<size_t>& groups);

  /**
   * @brief Compute the Weir and Cockerham @f$\theta_{wc}@f$ on a set of groups for a given set of loci and make a permutation test.
   * Multilocus @f$\theta@f$ is calculated as in getWCMultilocusFst on the original data set and on nb_perm data sets obtained after
   * a permutation of individuals between the different groups.
   * Return values are theta, % of values > theta and % of values < theta.
   */
  static PermResults getWCMultilocusFstAndPerm(
      const PolymorphismMultiGContainer& pmgc,
      std::vector<size_t> locusPositions,
      std::set<size_t> groups,
      unsigned int nb_perm);

  /**
   * @brief Compute the Weir and Cockerham Fis on a set of groups for a given set of loci and make a permutation test.
   * Multilocus Fis is calculated as in getWCMultilocusFis on the original data set and on nb_perm data sets obtained after
   * a permutation of alleles between individual of each group.
   * Return values are Fis, % of values > Fis and % of values < Fis.
   */
  static PermResults getWCMultilocusFisAndPerm(
      const PolymorphismMultiGContainer& pmgc,
      std::vector<size_t> locusPositions,
      std::set<size_t> groups,
      unsigned int nbPerm);


  /**
   * @brief Compute the @f$\theta_{RH}@f$ on a set of groups for a given set of loci.
   * The variance componenets for each allele are calculated and then combined over loci using RH weighting with alleles frequency.
   */
  static double getRHMultilocusFst(
      const PolymorphismMultiGContainer& pmgc,
      std::vector<size_t> locusPositions,
      const std::set<size_t>& groups);

  /**
   * @brief Compute pairwise distances on a set of groups for a given set of loci.
   * distance is either Nei72, Nei78, Fst W&C or Fst Robertson & Hill, Nm,
   * D=-ln(1-Fst) of Reynolds et al. 1983, Rousset 1997 Fst/(1-Fst)
   */
  static std::unique_ptr<DistanceMatrix> getDistanceMatrix(
      const PolymorphismMultiGContainer& pmgc,
      std::vector<size_t> locusPositions,
      const std::set<size_t>& groups,
      std::string distance_method);
};
} // end of namespace bpp;

#endif // _MULTILOCUSGENOTYPESTATISTICS_H_
