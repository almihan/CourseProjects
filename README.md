# Deeplearning Course Project (CSC 7343)

# CellExLink


### Prepraration

```bash
conda create -n CellExlink python=3.12
git clone https://github.com/CellExLink
cd CellExLink
pip install -r requirements.txt
```
This repository provides the code required to fine-tune the CellExLink NER and NEN models. Alternatively, the fine-tuned checkpoints can be downloaded directly from Hugging Face.
Download the fine-tuned checkpoints from Hugging Face and place them in the appropriate directories.

For the CellExLink NER component, download the checkpoint from [here](https://huggingface.co/almire/CellExLink-bioformer16L) and place it under `recognition/models/`.

For the CellExLink NEN component, download the checkpoint from [here](https://huggingface.co/almire/CellExLink-Sapbert) and place it under `normalization/models/`.

### Using CellExLink

#### NER prediction
```bash
from recognition import predict_ner

predict_ner(
    model_path="recognition/models/CellExLink-bioformer16L",
    input_xml="dataset/celllink/test.xml",
    output_dir="model_outputs/ner",
    output_xml="model_outputs/ner/predictions.xml",
)
```
#### NEN prediction
```bash
from normalization import normalize_bioc

normalize_bioc(
    input_xml="model_outputs/ner/predictions.xml",
    output_xml="model_outputs/normalized.xml",
    model_path="normalization/models/CellExLink-Sapbert",
)
```
### Fine-tuning
Fine-tune the NER model:

```bash
python recognition/src/run_fine_tune.py \
  --train-file train.json \
  --output-dir recognition/models/CellExLink-bioformer16L
```
Fine-tune the NEN model:

```bash
python normalization/fine_tune_sapbert.py \
  --train-pairs normalization/sapbert_data/sapbert_training_pairs.txt \
  --output-dir normalization/models/CellExLink-Sapbert
```

### Evaluation
Run NER-only evaluation:

```bash
python evaluation/run_eval_NER_only.py \
  --reference-path dataset/celllink/test.xml \
  --prediction-path model_outputs/ner/predictions.xml \
  --evaluation-method strict
```

Evaluation method can be `strict` or `relax`.

Run NEN evaluation:

```bash
python evaluation/run_eval.py \
  --dataset celllink \
  --reference-path dataset/celllink/test.xml \
  --prediction-path model_outputs/normalized.xml \
  --model-names SapBERT_finetuned \
  --score-mode identifier
```

- `--score-mode identifier`: evaluates only the correctness of the normalized identifier for gold-standard mentions.
- `--score-mode span_identifier`: evaluates both exact span matching and the correctness of the normalized identifier.

### Datasets
The CellLink, BioID, AnatEM, CRAFT, and JNLPBA datasets used in this project are available from the original Zenodo record: [link](https://zenodo.org/records/18090009).

Download the datasets from the original source and place them in the `dataset/` directory before running training or evaluation.

Use of these datasets is subject to the license and terms specified by the original source. Please refer to the Zenodo record for citation and licensing information.


