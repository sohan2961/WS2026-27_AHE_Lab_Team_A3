#!/usr/bin/env python3
"""Ensure the shared Excel tracker and Markdown checkpoint plan agree exactly.

No third-party dependencies. Run from any working directory:
    python3 scripts/check_checkpoint_sync.py
"""

from collections import Counter
from pathlib import Path, PurePosixPath
import re
import sys
import xml.etree.ElementTree as ET
from zipfile import ZipFile


ROOT = Path(__file__).resolve().parents[1]
BOOK = ROOT / "tracking" / "Weekly_Updates.xlsx"
PLAN = ROOT / "tracking" / "CHECKPOINTS_18.md"
MAIN_NS = "http://schemas.openxmlformats.org/spreadsheetml/2006/main"
REL_NS = "http://schemas.openxmlformats.org/officeDocument/2006/relationships"
PKG_REL_NS = "http://schemas.openxmlformats.org/package/2006/relationships"


def load_excel_tasks():
    with ZipFile(BOOK) as file:
        workbook = ET.fromstring(file.read("xl/workbook.xml"))
        sheets = workbook.find(f"{{{MAIN_NS}}}sheets")
        check_sheet = next(s for s in sheets if s.attrib.get("name") == "Weekly Checkpoints")
        relationship_id = check_sheet.attrib[f"{{{REL_NS}}}id"]
        rel_root = ET.fromstring(file.read("xl/_rels/workbook.xml.rels"))
        relationship = next(x for x in rel_root if x.attrib.get("Id") == relationship_id)
        target = relationship.attrib["Target"]
        if target.startswith("/"):
            sheet_name = target.lstrip("/")
        else:
            sheet_name = str(PurePosixPath("xl") / target)
        # A fixed tracker should not contain spreadsheet path traversal.
        if ".." in PurePosixPath(sheet_name).parts:
            raise ValueError("Unexpected worksheet path")
        sheet = ET.fromstring(file.read(sheet_name))
        strings = []
        if "xl/sharedStrings.xml" in file.namelist():
            shared = ET.fromstring(file.read("xl/sharedStrings.xml"))
            for item in shared.findall(f"{{{MAIN_NS}}}si"):
                strings.append("".join(t.text or "" for t in item.iter(f"{{{MAIN_NS}}}t")))

        cells = {}
        for cell in sheet.iter(f"{{{MAIN_NS}}}c"):
            ref = cell.attrib.get("r", "")
            value_element = cell.find(f"{{{MAIN_NS}}}v")
            if cell.attrib.get("t") == "inlineStr":
                inline = cell.find(f"{{{MAIN_NS}}}is")
                value = "".join(t.text or "" for t in inline.iter(f"{{{MAIN_NS}}}t")) if inline is not None else ""
            elif value_element is not None:
                value = value_element.text or ""
                if cell.attrib.get("t") == "s":
                    value = strings[int(value)]
            else:
                value = ""
            cells[ref] = value

        records = []
        for row in range(12, 30):
            records.append((int(cells[f"B{row}"]), cells[f"C{row}"], cells[f"A{row}"]))
        return records


def load_markdown_tasks():
    tasks = []
    for line in PLAN.read_text(encoding="utf-8").splitlines():
        match = re.match(r"^\|\s*(\d{1,2})\s*\|\s*(.*?)\s*\|", line)
        if match:
            tasks.append((int(match.group(1)), match.group(2)))
    return tasks


def verify_weekly_files(excel):
    titles = {task_id: title for task_id, title, _ in excel}
    for week, allowed in ((1, range(1, 6)), (2, range(6, 11)), (3, range(11, 15)), (4, range(15, 19))):
        folder = ROOT / "weekly_work" / f"week_0{week}"
        week_rows = []
        for line in (folder / "README.md").read_text(encoding="utf-8").splitlines():
            match = re.match(r"^\|\s*(\d{1,2})\s*\|\s*(.*?)\s*\|", line)
            if match:
                week_rows.append((int(match.group(1)), match.group(2)))
        assert week_rows == [(i, titles[i]) for i in allowed], f"Week {week} overview titles differ"
        for member in ("mostafizur", "turja", "deepak"):
            member_file = folder / member / "README.md"
            headings = [
                (int(match.group(1)), match.group(2))
                for line in member_file.read_text(encoding="utf-8").splitlines()
                if (match := re.match(r"^### CP(\d{2}) — (.+)$", line))
            ]
            assert headings, f"No assigned checkpoint titles in {member_file}"
            for task_id, title in headings:
                assert task_id in allowed, f"Wrong week: {member_file} CP{task_id}"
                assert title == titles[task_id], f"Member title mismatch: {member_file} CP{task_id}"


def main():
    excel = load_excel_tasks()
    markdown = load_markdown_tasks()
    assert len(excel) == len(markdown) == 18, "Must have exactly 18 checkpoints in both files"
    for (excel_id, excel_title, _), (md_id, md_title) in zip(excel, markdown):
        assert excel_id == md_id, f"Checkpoint ID mismatch: Excel {excel_id}; Markdown {md_id}"
        assert excel_title == md_title, f"Checkpoint {excel_id} title mismatch:\n  Excel: {excel_title!r}\n  Markdown: {md_title!r}"
    counts = Counter(week for _, _, week in excel)
    assert counts == {"Week 1": 5, "Week 2": 5, "Week 3": 4, "Week 4": 4}, counts
    verify_weekly_files(excel)
    print("PASS: 18 exact checkpoint names across Excel, plan, weekly overviews and all member folders; IDs 1–18, weeks 5/5/4/4.")


if __name__ == "__main__":
    try:
        main()
    except (AssertionError, KeyError, ValueError, OSError) as error:
        print(f"FAIL: {error}", file=sys.stderr)
        sys.exit(1)
