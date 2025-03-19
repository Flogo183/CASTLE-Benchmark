# CASTLE Benchmark

<div align="center">
    <img width="300" alt="Logo of the CASTLE Benchmark" src="./assets/castle-benchmark-logo.png">
</div>

The __CASTLE Benchmark__ is a comprehensive dataset and a scoring method for evaluating single or combinations of __static analyzers__ with a focus on security. It consists of a hand-crafted dataset of __250__ micro-benchmark programs (almost 11,000 lines of C code), covering __25__ common __CWEs__. We also introduce the novel __CASTLE Score__ metric to enable fair and reliable comparisons, considering factors such as true positive and false positive rates, as well as the tools' ability to find more common issues. This dataset enables a comparison of single tools, as well as the effectiveness of tool combinations.

## The Complete Dataset

- [CASTLE-C250.json](./datasets/CASTLE-C250.json) - The parsed and labeled dataset with 250 tests in C language.
- [CASTLE-C250.min.json](./datasets/CASTLE-C250.min.json) - The minified version parsed and labeled dataset with 250 tests in C language. It contains everything from the non-minimized version but it's less readable: recommended for automated use.
- [CASTLE-C250](./datasets/CASTLE-C250) - All 250 tests in C language in individual C files with an accompanied Makefile.
