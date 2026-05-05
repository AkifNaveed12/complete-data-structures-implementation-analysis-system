# 🚀 Git Workflow Rules – CDSIAS

## 🎯 Objective

Maintain a clean, professional, and synchronized repository where:

- `main` always contains stable, tested code
- `akif-dev` is used for active development
- No commits are lost or hidden
- No branch drift occurs

---

## 🌿 Branch Strategy

### 🔹 main

- Stable production-ready code
- Always tested
- Always runnable
- Used for demos and submissions

### 🔹 akif-dev

- Active development branch
- All new features, fixes, and experiments happen here first

---

## 🔁 Workflow (MANDATORY)

For every feature/task:

1. Work ONLY on `akif-dev`

2. Implement feature

3. Compile and test completely

4. Validate:
   - No errors
   - Correct output
   - Visualization working
   - Performance logging correct

5. Commit to `akif-dev`

6. Merge into `main`:

```bash
git checkout main
git pull origin main
git merge akif-dev
git push origin main
```

7. Switch back:

```bash
git checkout akif-dev
```

---

## 🚫 Strict Rules

- ❌ NEVER commit directly to main
- ❌ NEVER leave main outdated
- ❌ NEVER skip testing before merge
- ❌ NEVER break existing working code
- ❌ NEVER leave unmerged commits in akif-dev

---

## 📦 Commit Message Convention

Use professional format:

- feat(module): add new feature
- fix(module): bug fix
- refactor(module): improve structure
- docs: documentation updates
- test(module): add/update tests

### Examples:

- feat(array): add insertAt visualization
- fix(linkedlist): correct traversal logic
- docs: update context and architecture

---

## 🔍 Pre-Merge Checklist

Before merging to main:

- [ ] Code compiles
- [ ] All modules tested
- [ ] No runtime errors
- [ ] Visualization correct
- [ ] Performance logs correct
- [ ] context.md updated

---

## 🧠 Context Sync Rule

After every meaningful change:

Update:

```
docs/context.md
```

Include:

- File modified
- Function modified
- What changed
- Why changed

---

## ⚠️ Issue Prevention

- Always check current branch before commit
- Always push `akif-dev` before merging
- Always pull `main` before merging
- Avoid merge conflicts
- Ensure GitHub `main` is always up-to-date

---

## 🔄 Continuous Integration Mindset

Each task cycle:

```
Develop → Test → Commit → Merge → Push → Verify
```

---

## 🚀 Final Goal

- Clean commit history
- Stable main branch
- Controlled development flow
- No lost or hidden changes
