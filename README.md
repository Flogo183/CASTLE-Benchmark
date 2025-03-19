# CASTLE Benchmark

<div align="center">
    <img width="300" alt="Logo of the CASTLE Benchmark" src="./assets/castle-benchmark-logo.png">
</div>

The __CASTLE Benchmark__ is a comprehensive dataset and a scoring method for evaluating single or combinations of __static analyzers__ with a focus on security. It consists of a hand-crafted dataset of __250__ micro-benchmark programs (almost 11,000 lines of C code), covering __25__ common __CWEs__. We also introduce the novel __CASTLE Score__ metric to enable fair and reliable comparisons, considering factors such as true positive and false positive rates, as well as the tools' ability to find more common issues. This dataset enables a comparison of single tools, as well as the effectiveness of tool combinations.

This dataset was created by Richard A. Dubniczky, Krisztofer Zoltan Horvát, Tamás Bisztray,
Mohamed Amine Ferrag, Lucas C. Cordeiro, and Norbert Tihanyi as a joint research project and it is currently under peer-review.

## The Complete Dataset

- [CASTLE-C250.json](./datasets/CASTLE-C250.json) - The parsed and labeled dataset with 250 tests in C language.
- [CASTLE-C250.min.json](./datasets/CASTLE-C250.min.json) - The minified version parsed and labeled dataset with 250 tests in C language. It contains everything from the non-minimized version but it's less readable: recommended for automated use.
- [CASTLE-C250](./datasets/CASTLE-C250) - All 250 tests in C language in individual C files with an accompanied Makefile.

## Framework

![CASTLE Framework Diagram](./assets/castle-framework.png)

The CASTLE Framework consists of 4 main stages:

1. We selected the tested CWEs, created the dataset of tests and labelings and validated the correctness of the C code over many iterations using expert review, static analyzers, formal verification methods, and LLMs. The final result from this step is the dataset JSON file.
2. In the second step we created wrappers for all tools to automate the evaluation as much as possible. For some open-source tools this means running the tests in a container in sequence, while for others we had to access APIs or manually download the results and parse them afterwards. The output of this step is an report JSON file in a custom common format.
3. In the manual review phase we looked at all the ~7,500 findings and validated our TP and FP classifications. Some tools marked a different line or CWE than our tests indicate, and in those cases we set our classification accordingly and updated our tests. We ran these tests on the tools at least 3 times between Nov 2024 and Feb 2025 with the updated dataset.
4. We evaluated the findings and calculated the CASTLE Score for single tools and tool combinations, as well as generated our final toplists and charts.