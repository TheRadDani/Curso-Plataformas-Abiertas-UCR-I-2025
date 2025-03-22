# Class 6: Advanced GitHub for Library Development and Collaboration
## Author: Daniel Ferreto

## Table of Contents
1. [Introduction to GitHub for Software Libraries](#1-introduction)
2. [Creating Reusable Libraries](#2-creating-libraries)
3. [Git Submodules](#3-git-submodules)
4. [Releases and Versioning](#4-releases-and-versioning)
5. [Advanced Collaboration](#5-advanced-collaboration)
6. [Practical Example Project](#6-practical-example)
7. [Best Practices](#7-best-practices)
8. [Additional Resources](#8-resources)

---

<a name="1-introduction"></a>
## 1. Introduction to GitHub for Software Libraries

GitHub is not just for code hosting – it’s a platform for **building maintainable software**. Key concepts for library development:
- **Repositories as libraries**: Design repos to be imported/used by others
- **Semantic Versioning**: `MAJOR.MINOR.PATCH` (e.g., `1.4.2`)
- **Documentation**: README.md, CONTRIBUTING.md, API references
- **Automation**: GitHub Actions for CI/CD, testing, and publishing

---

What is a PATCH?
A PATCH update is meant to fix errors or bugs in the software without introducing new features or breaking existing functionality. It's the smallest level of change in semantic versioning.

Examples of PATCH updates:
Software Bug Fixes:

A problem that caused incorrect results in calculations is corrected.

Version changes from `1.0.1 to 1.0.2.`

Security Vulnerability Fixes:

Addressing a vulnerability in authentication without altering APIs.

Version changes from `2.3.5 to 2.3.6.`

Performance Improvements:

Optimizing a specific function's runtime while maintaining the same output.

Version changes from `1.4.2 to 1.4.3.`

---

<a name="2-creating-libraries"></a>
## 2. Creating Reusable Libraries

### Library Structure Example
```bash
my-library/
├─ src/               # Source code
│  ├─ index.js        # Main entry point
│  └─ utils.js        # Helper functions
├─ test/              # Unit/integration tests
├─ docs/              # Documentation
├─ .github/           # GitHub workflows
├─ package.json       # Metadata (npm) or pyproject.toml (Python)
├─ LICENSE            # Legal terms
└─ README.md          # User/developer guide
```

### Key Steps to Publish a Library
1. **Initialize repository** with proper `.gitignore`
2. **Add build systems** (Webpack, Rollup, Poetry, etc.)
3. **Write tests** (Jest, pytest, etc.)
4. **Configure CI/CD** (GitHub Actions example):

## What Are GitHub Actions?

GitHub Actions is a feature of GitHub that allows you to automate your software development workflows. With Actions, you can:
- Run tests automatically.
- Build and deploy your applications.
- Integrate with external services.
- Automate repetitive tasks like linting or formatting.

**Key Features:**
- **Workflows**: Define tasks to run in response to events (e.g., code pushed to the repository).
- **Actions**: Individual steps in a workflow.
- **Triggers**: Specify when workflows should run (e.g., on `push`, `pull_request`).

---

## Basic Structure of a Workflow File

A GitHub Actions workflow is defined in a YAML file located in the `.github/workflows/` directory. Here’s the basic structure:

```yaml
# Example workflow file
name: Workflow Name  # Name of the workflow
on: [event]          # Event that triggers the workflow
jobs:                # Define jobs
  job_name:          # Name of the job
    runs-on:         # Specify the runner (e.g., ubuntu-latest)
    steps:           # List of steps in the job
      - name: Step description
        run: Command to execute
```

---

### 2. Setting Up GitHub Actions for Python <a name="setup-python"></a>

#### Sample Workflow for Python CI
This workflow installs Python dependencies, runs tests, and checks for linting issues.

```yaml
# .github/workflows/python-ci.yml
name: Python CI

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Set up Python
        uses: actions/setup-python@v4
        with:
          python-version: "3.9"

      - name: Install dependencies
        run: |
          python -m pip install --upgrade pip
          pip install -r requirements.txt

      - name: Run tests
        run: pytest

      - name: Check linting
        run: |
          pip install flake8
          flake8 .
```

1. Checkout Code: Pulls the repository’s code into the runner.

2. Setup Python: Installs the specified version of Python.

3. Install Dependencies: Installs required packages listed in requirements.txt.

4. Run Tests: Executes unit tests using pytest.

5. Check Linting: Ensures your code adheres to style guidelines with flake8.


## Setting Up GitHub Actions for C <a name="setup-c"></a>
Sample Workflow for C CI
This workflow compiles a C project, runs tests, and performs static code analysis.

```yaml
# .github/workflows/c-ci.yml
name: C CI

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Install build tools
        run: |
          sudo apt-get update
          sudo apt-get install -y build-essential

      - name: Build project
        run: |
          gcc -o output main.c
          ./output

      - name: Run tests
        run: ./test-suite

      - name: Static code analysis
        run: |
          sudo apt-get install -y cppcheck
          cppcheck --enable=all .
```

1. Checkout Code: Pulls the repository’s code into the runner.

2. Install Build Tools: Ensures gcc and other essential tools are installed.

3. Build Project: Compiles the C source code and runs the executable.

4. Run Tests: Executes your test suite to validate functionality.

5. Static Code Analysis: Uses `cppcheck` to detect potential issues in the code.


## Parallel Jobs
Run multiple jobs concurrently to speed up workflows. Example:

```yaml
jobs:
  lint:
    runs-on: ubuntu-latest
    steps:
      - name: Lint Code
        run: flake8 .
  tests:
    runs-on: ubuntu-latest
    steps:
      - name: Run Tests
        run: pytest
```

## Matrix Builds
Test your project on multiple environments or configurations:
```yaml
jobs:
  test:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        python-version: ["3.8", "3.9", "3.10"]
    steps:
      - uses: actions/setup-python@v4
        with:
          python-version: ${{ matrix.python-version }}
      - run: pytest
```

## Best Practices <a name="best-practices"></a>
Keep Workflows Modular: Use separate workflows for testing, building, and deployment.

Use Caching: Cache dependencies to speed up workflows. Example for Python:

```yaml
- uses: actions/cache@v4
  with:
    path: ~/.cache/pip
    key: ${{ runner.os }}-pip-${{ hashFiles('**/requirements.txt') }}
    restore-keys: |
      ${{ runner.os }}-pip-
```

Automate Documentation: Use tools like Sphinx for Python or Doxygen for C, combined with GitHub Pages.

Monitor Workflow Performance: Regularly optimize steps for faster execution.

Example:
```bash
  sudo apt-get update
  sudo apt-get install doxygen
```

```c
/**
 * @file main.c
 * @brief This file demonstrates a basic program for Doxygen documentation.
 * @author Luis
 * @date 2025-03-21
 */

#include <stdio.h>

/**
 * @brief Adds two integers.
 * 
 * This function takes two integers as inputs and returns their sum.
 * 
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of a and b.
 */
int add(int a, int b) {
    return a + b;
}

/**
 * @brief Main function.
 * 
 * The entry point of the program that demonstrates the `add` function.
 * 
 * @return 0 on success.
 */
int main() {
    int result = add(5, 3);
    printf("The sum is: %d\n", result);
    return 0;
}
```

Generate a configuration file using the doxygen command
```bash
doxygen -g
```


This will create a file named `Doxyfile`. Open it in a text editor and modify the following key options:
```bash
PROJECT_NAME = "Example C Project"
INPUT = ./main.c
GENERATE_HTML = YES
GENERATE_LATEX = YES
HAVE_DOT = YES
```

Run the following command to generate the documentation
```bash
sudo apt-get install graphviz -y
doxygen Doxyfile
```
```bash
git checkout -b gh-pages
git push origin gh-pages
```

You can automate the documentation generation process and deploy it to GitHub Pages. Here’s an example workflow
```yaml
# .github/workflows/main.yml
name: Doxygen Documentation Automation

on:
  push:
    branches:
      - main
  pull_request:
    branches:
      - main

jobs:
  generate-docs:
    runs-on: ubuntu-latest

    steps:
      # Step 1: Checkout the repository
      - name: Checkout Code
        uses: actions/checkout@v4

      # Step 2: Install Doxygen
      - name: Install Doxygen
        run: |
          sudo apt-get update
          sudo apt-get install -y doxygen graphviz

      # Step 3: Generate the Documentation
      - name: Generate Documentation
        run: doxygen Doxyfile

      # Step 4: Deploy to GitHub Pages
      - name: Deploy to GitHub Pages
        uses: peaceiris/actions-gh-pages@v3
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./html/index.html
```