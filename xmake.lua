set_project("ExampleOS")

add_rules("mode.debug", "mode.release")
add_requires("zig", "nasm")

set_arch("i386")
set_optimize("fastest")
set_warnings("all", "extra")
set_policy("run.autobuild", true)

target("kernel")
    set_kind("binary")
    set_languages("c23")
    set_toolchains("@zig", "nasm")
    set_default(false)

    add_includedirs("include")
    add_files("src/**.asm", "src/**.c")

    add_asflags("-f", "elf32", {force = true})

    -- Fix xmake arch setting for Zig, see issue #5763
    add_cflags("-target x86-freestanding", {force = true})
    add_ldflags("-target x86-freestanding", {force = true})

    add_ldflags("-flto", "-T", "linker.ld", {force = true})
    add_cflags("-flto", "-m32", {force = true})
    add_cflags("-mno-80387", "-mno-mmx", "-mno-sse", "-mno-sse2", {force = true})

target("iso")
    set_kind("phony")
    add_deps("kernel")
    set_default(true)

    on_build(function (target)
        import("core.project.project")
        local iso_dir = "$(buildir)/iso_dir"

        if os.exists(iso_dir) then
            os.rmdir(iso_dir)
        end

        os.cp("assets", iso_dir)
        local target = project.target("kernel")
        os.cp(target:targetfile(), iso_dir .. "/kernel.elf")
        local iso_file = "$(buildir)/exampleos.iso"

        -- GRUB Build ISO (commented out)
        -- os.run("grub-mkrescue -o %s %s", iso_file, iso_dir)

        -- Limine Build ISO
        local xorriso_flags = "-b limine/limine-bios-cd.bin -no-emul-boot -boot-info-table"
        os.run("xorriso -as mkisofs %s %s -o %s", xorriso_flags, iso_dir, iso_file)

        print("ISO image created at: " .. iso_file)
    end)

    on_run(function (target)
        import("core.project.config")

        local flags = {
            "-M", "q35",
            "-serial", "stdio",
            "-cdrom", config.buildir() .. "/exampleos.iso"
        }
        
        os.runv("qemu-system-x86_64", flags)
    end)
